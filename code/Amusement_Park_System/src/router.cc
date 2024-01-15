#include "router.h"

using namespace std;

void
RoutingHandler::handle()
{
    router_->routingHandler();
}

Router::Router() : routingHandler_(this)
{
    //ctor
}

void
Router::initialize(SimObject* terminator)
{
    expiredRouteEvent_ = 0;
    terminator_ = terminator;

    RouterPolicy rp = Policy::getRouterPolicy();

    setRouteMean(rp.routeMean);
}

void
Router::setRouteMean(double value)
{
    routeMean_ = value;
}

void
Router::setDestinations(std::vector <SimObject*> destinations)
{
    destinations_ = destinations;
}

double
Router::exponential(double mean)
{
    double r = (double)rand()/RAND_MAX;
    while (r <= 0) r = (double)rand()/RAND_MAX;
    double ex = - mean * log (r);
    return ex;
}

void
Router::clearExpiredRouteEvent()
{
    if(expiredRouteEvent_)
    {
        delete expiredRouteEvent_;
        expiredRouteEvent_ = 0;
    }
}

Event*
Router::getRoutingEvent()
{
    Event* targetRouteEvent = 0;

    for(auto curRouteEvent : routeEvents_)
    {
        if(!curRouteEvent->busy())
        {
            targetRouteEvent = curRouteEvent;
            break;
        }
    }

    auto targetIter = find(routeEvents_.begin(), routeEvents_.end(), targetRouteEvent);

    if(targetIter != routeEvents_.end())
    {
        routeEvents_.erase(targetIter);
    }

    return targetRouteEvent;
}

Visitor*
Router::getRoutingVisitor()
{
    Visitor* targetVisitor = 0;

    for(auto curVisitor : visitors_)
    {
        if(expiredRouteEvent_->eventType() == 1000 + curVisitor->id())
        {
            targetVisitor = curVisitor;
            break;
        }
    }

    auto targetIter = find(visitors_.begin(), visitors_.end(), targetVisitor);

    if(targetIter != visitors_.end())
    {
        visitors_.erase(targetIter);
    }

    return targetVisitor;
}

SimObject*
Router::getRoutingDestination()
{
    int targetDestination = routingVisitor_->getNextDestination();

    if(targetDestination == -1) return terminator_;

    return destinations_[targetDestination];
}

void
Router::routeVisitor(double routeDelay)
{
    clearExpiredRouteEvent();

    Event* tempR = new Event();
    tempR->eventType() = 1000 + receivedVisitor_->id();
    tempR->schedule(&routingHandler_, routeDelay);

    routeEvents_.push_back(tempR);
}

void
Router::receiveHandler()
{
    visitors_.push_back(receivedVisitor_);

    double routeDelay = exponential(routeMean_);
    routeVisitor(routeDelay);
}

void
Router::routingHandler()
{
    expiredRouteEvent_ = getRoutingEvent();
    routingVisitor_ = getRoutingVisitor();
    target_ = getRoutingDestination();
    send(routingVisitor_);
}

void
Router::send (Visitor* visitor)
{
    target_->recv(visitor);
}

void
Router::recv (Visitor* visitor)
{
    receivedVisitor_ = visitor;
    receiveHandler();
}

Router::~Router()
{
    //dtor
}

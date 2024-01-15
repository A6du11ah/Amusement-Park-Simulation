#ifndef ROUTER_H
#define ROUTER_H

#include <time.h>
#include <math.h>
#include <malloc.h>
#include <cstdbool>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "event.h"
#include "scheduler.h"
#include "visitor.h"
#include "SimObject.h"
#include "policy.h"

class Router;

class RoutingHandler : public Handler
{
public:
    RoutingHandler (Router* r) : router_(r) {}
    void handle ();

protected:
    Router* router_;
};

class Router : public SimObject
{
public:
    Router();

    void initialize(SimObject* terminator);

    void setRouteMean(double value);
    void setDestinations(std::vector <SimObject*> destinations);

    void routingHandler();

    void send (Visitor* visitor);
    void recv (Visitor* visitor);

    virtual ~Router();

protected:

private:
    int crowdStatus_;

    SimObject* terminator_;

    std::vector <SimObject*> destinations_;
    std::vector <Visitor*> visitors_;

    Visitor* receivedVisitor_;
    Visitor* routingVisitor_;

    Event* expiredRouteEvent_;

    std::vector <Event*> routeEvents_;
    RoutingHandler routingHandler_;

    double routeMean_;

    Event* getRoutingEvent();
    Visitor* getRoutingVisitor();
    SimObject* getRoutingDestination();

    void clearExpiredRouteEvent();

    double exponential(double mean);

    void receiveHandler();

    void routeVisitor(double routeDelay);
};

#endif // ROUTER_H

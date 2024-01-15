#include "server.h"

using namespace std;

void
LoadingHandler :: handle ()
{
    server_->loadingHandler();
}

void
ServiceHandler :: handle ()
{
    server_->serviceHandler();
}

Server :: Server() : loadingHandler_(this), serviceHandler_(this)
{
    status_ = ServerState::IDLE;

    serviceQueue_ = new Queue();

    loadEvent_ = new Event();
    loadEvent_->eventType() = 1;

    serveEvent_ = new Event();
    serveEvent_->eventType() = 2;
}

void
Server :: initialize (int id = 0, int batchSize = 1, bool allowLoading = false)
{
    id_ = id;
    batchSize_ = batchSize;
    allowLoading_ = allowLoading;

    if (allowLoading_)
    {
        scheduleLoading();
    }
}

void
Server :: setLoadingTime (double value)
{
    loadingTime_ = value;
}

void
Server :: setServiceTime (double value)
{
    serviceTime_ = value;
}

void
Server :: assignTerminal(SimObject* terminal)
{
    terminal_ = terminal;
}

bool
Server :: checkStatus(ServerState expectedState)
{
    return (status_ == expectedState);
}

void
Server :: updateStatus(ServerState newState)
{
    status_ = newState;
}


void
Server :: calcStats()
{
    double currentTime = Scheduler::now();

    Record* record = departingVisitor_->getCurrentDestinationRecord();

    record->serviceTime_ = serviceTime_;
    record->delay_ = currentTime - record->arrivalTime_;
}

void
Server :: scheduleLoading()
{
    loadEvent_->schedule(&loadingHandler_, loadingTime_);
}

void
Server :: scheduleService()
{
    serveEvent_->schedule(&serviceHandler_, serviceTime_);
}

void
Server :: receiveHandler()
{
    serviceQueue_->enque(receivedVisitor_);

    if(serviceQueue_->length() == batchSize_)
    {
        updateStatus(ServerState::BUSY);
        scheduleService();
    }
}

void
Server :: loadingHandler()
{
    if(serviceQueue_->isEmpty())
    {
        scheduleLoading();
    }
    else if(checkStatus(ServerState::IDLE))
    {
        updateStatus(ServerState::BUSY);
        scheduleService();
    }
}

void
Server :: serviceHandler()
{
    while(!serviceQueue_->isEmpty())
    {
        departingVisitor_ = serviceQueue_->dque();

        calcStats();

        send(departingVisitor_);
    }

    updateStatus(ServerState::IDLE);

    if (allowLoading_)
    {
        scheduleLoading();
    }

    signal(0);
}

void
Server :: send (Visitor* visitor)
{
    target_->recv(visitor);
}

void
Server :: recv (Visitor* visitor)
{
    receivedVisitor_ = visitor;
    receiveHandler();
}

void
Server :: signal(int msg)
{
    terminal_->respond(id_, msg);
}

void
Server :: respond(int obj, int msg)
{
    //TODO
}

Server::~Server()
{
    //dtor
}

#include "terminal.h"

using namespace std;

Terminal::Terminal()
{
    //ctor
}

void
Terminal::initialize(int noOfServers, bool allowStrictFCFS, bool allowFastPass)
{
    lastArrivalTime_ = 0;

    noOfServers_ = noOfServers;

    allowStrictFCFS_ = allowStrictFCFS;
    allowFastPass_ = allowFastPass;

    if(allowStrictFCFS)
    {
        gQueue_ = new Queue();
    }
    else
    {
        Queue* tempQ;

        for(int i = 0; i < noOfServers_; i++)
        {
            tempQ = new Queue;
            dQueues_.push_back(tempQ);
        }
    }

    if(allowFastPass)
    {
        fpQueue_ = new Queue;
    }
}

void
Terminal::setServerList(std::vector <Server*> servers)
{
    servers_ = servers;
}

Server*
Terminal::findServer(int id)
{
    if(id < (int)servers_.size()) return servers_[id];

    return 0;
}

Queue*
Terminal::findQueue(int serverId)
{
    if(allowStrictFCFS_) return gQueue_;

    if(serverId < (int)dQueues_.size()) return dQueues_[serverId];

    return 0;
}

Server*
Terminal::findIdleServer()
{
    for(auto curServer : servers_)
    {
        if(curServer->checkStatus(ServerState::IDLE))
        {
            return curServer;
        }
    }

    return 0;
}

Queue*
Terminal::findShortQueue()
{
    Server* targetServer = 0;
    int minServerSize = INT_MAX;

    for(auto curServer : servers_)
    {
        Queue* curServerQueue = findQueue(curServer->getId());
        int curServerSize = (int)curServer->getStatus() + curServerQueue->length();

        if(curServerSize < minServerSize)
        {
            targetServer = curServer;
            minServerSize = curServerSize;
        }
    }

    return findQueue(targetServer->getId());
}

void
Terminal::serveVisitor(Server* idleServer)
{
    idleServer->recv(servingVisitor_);
}

void
Terminal::calcStats()
{
    double currentTime = Scheduler::now();

    Record* record = receivedVisitor_->getCurrentDestinationRecord();

    record->arrivalTime_ = currentTime;
    record->interArrivalTime_ = currentTime - lastArrivalTime_;

    lastArrivalTime_ = currentTime;
}

void
Terminal::receiveHandler()
{
    calcStats();

    Server* idleServer = findIdleServer();

    if(idleServer)
    {
        servingVisitor_ = receivedVisitor_;
        serveVisitor(idleServer);
    }
    else if(allowFastPass_ && receivedVisitor_->type() == 1)
    {
        fpQueue_->enque(receivedVisitor_);
    }
    else
    {
         Queue* waitQueue = findShortQueue();
         waitQueue->enque(receivedVisitor_);
    }
}

void
Terminal::signalHandler()
{
    Server* signalingServer = findServer(signalingServerIdx_);
    Queue* waitingQueue = findQueue(signalingServerIdx_);

    while(signalingServer->checkStatus(ServerState::IDLE))
    {
        if(allowFastPass_ && !fpQueue_->isEmpty())
        {
            waitingVisitor_ = fpQueue_->dque();
        }
        else if(!waitingQueue->isEmpty())
        {
            waitingVisitor_ = waitingQueue->dque();
        }
        else
        {
            break;
        }

        servingVisitor_ = waitingVisitor_;
        serveVisitor(signalingServer);
    }
}

void
Terminal::send(Visitor* visitor)
{
    target_->recv(visitor);
}

void
Terminal::recv(Visitor* visitor)
{
    receivedVisitor_ = visitor;
    receiveHandler();
}

void
Terminal::signal(int msg)
{
    //TODO
}

void
Terminal::respond(int obj, int msg)
{
    signalingServerIdx_ = obj;
    signalHandler();
}

Terminal::~Terminal()
{
    //dtor
}

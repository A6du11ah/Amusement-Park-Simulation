#ifndef SERVER_H
#define SERVER_H

#include <cstdbool>

#include "event.h"
#include "scheduler.h"
#include "visitor.h"
#include "queue.h"
#include "SimObject.h"

enum class ServerState {IDLE, BUSY};

class Server;

class LoadingHandler : public Handler
{
public:
    LoadingHandler (Server* s) : server_(s) {}
    void handle ();

protected:
    Server* server_;
};

class ServiceHandler : public Handler
{
public:
    ServiceHandler (Server* s) : server_(s) {}
    void handle ();

protected:
    Server* server_;
};

class Server : public SimObject
{
public:
    Server();

    void initialize(int id, int batchSize, bool allowLoading);

    inline int getId() { return id_; }
    inline int getBatchSize() { return batchSize_; }

    inline ServerState getStatus() { return status_; }

    void setLoadingTime (double value);
    void setServiceTime (double value);

    bool checkStatus(ServerState expectedState);

    void assignTerminal(SimObject* terminal);

    void loadingHandler();
    void serviceHandler();

    void send (Visitor* visitor);
    void recv (Visitor* visitor);

    void signal(int msg);
    void respond(int obj, int msg);

    virtual ~Server();

protected:

private:
    int id_;
    int batchSize_;
    bool allowLoading_;

    ServerState status_;
    Queue* serviceQueue_;

    SimObject* terminal_;

    Event* loadEvent_;
    LoadingHandler loadingHandler_;

    Event* serveEvent_;
    ServiceHandler serviceHandler_;

    Visitor* receivedVisitor_;
    Visitor* departingVisitor_;

    double loadingTime_;
    double serviceTime_;

    void updateStatus(ServerState newState);

    void calcStats();

    void receiveHandler();

    void scheduleLoading();
    void scheduleService();
};

#endif // SERVER_H

#ifndef TERMINAL_H
#define TERMINAL_H

#include <time.h>
#include <math.h>
#include <malloc.h>
#include <cstdbool>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>

#include "event.h"
#include "scheduler.h"
#include "visitor.h"
#include "queue.h"
#include "SimObject.h"
#include "server.h"

class Terminal : public SimObject
{
public:
    Terminal();

    void initialize (int noOfServers, bool allowStrictFCFS, bool allowFastPass);
    void setServerList(std::vector <Server*> servers);

    void send (Visitor* visitor);
    void recv (Visitor* visitor);

    void signal(int msg);
    void respond(int obj, int msg);

    virtual ~Terminal();

protected:

private:
    int noOfServers_;

    bool allowStrictFCFS_;
    bool allowFastPass_;

    std::vector <Server*> servers_;

    Queue* gQueue_;
    Queue* fpQueue_;
    std::vector <Queue*> dQueues_;

    Visitor* receivedVisitor_;
    Visitor* servingVisitor_;
    Visitor* waitingVisitor_;

    int signalingServerIdx_;

    double lastArrivalTime_;

    void calcStats();

    void receiveHandler();
    void signalHandler();

    Server* findIdleServer();
    Queue* findShortQueue();

    Server* findServer(int id);
    Queue* findQueue(int serverId);

    void serveVisitor(Server* idleServer);
};

#endif // TERMINAL_H

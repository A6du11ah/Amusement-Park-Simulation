#ifndef TERMINATOR_H
#define TERMINATOR_H

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
#include "generator.h"
#include "server.h"
#include "terminal.h"
#include "router.h"

#include "policy.h"

class Terminator;

class TerminationHandler : public Handler
{
public:
    TerminationHandler (Terminator* t) : terminator_(t) {}
    void handle ();

protected:
    Terminator* terminator_;
};

class Terminator : public SimObject
{
public:
    Terminator();

    void initialize (Generator* generator);

    void terminationHandler();

    void send (Visitor* visitor);
    void recv (Visitor* visitor);

    virtual ~Terminator();

protected:

private:
    Generator* generator_;

    int visitorTerminated_;
    Visitor* receivedVisitor_;

    double terminationTime_;

    Event* terminationEvent_;
    TerminationHandler terminationHandler_;

    bool allowCompleteTermination_;

    void saveStats();

    void scheduleTermination();
    void completeTermination();

    void receiveHandler();
};

#endif // TERMINATOR_H

#ifndef GENERATOR_H
#define GENERATOR_H

#include <cstdlib>
#include <cstdbool>
#include <math.h>

#include "SimObject.h"
#include "event.h"
#include "scheduler.h"
#include "policy.h"

class Generator;

class GeneratorHandler : public Handler
{
public:
    GeneratorHandler (Generator* g) : generator_(g) {}
    void handle ();

protected:
    Generator* generator_;
};

class Generator : public SimObject
{
public:
    Generator();

    inline double& arrivalMean () { return (arrivalMean_); }
    inline int& visitorArrived ()  { return (visitorArrived_); }

    void initialize ();

    void scheduleArrival ();
    void generatorHandler ();

    void send (Visitor* visitor);
    void recv (Visitor* visitor);

    virtual ~Generator();

protected:

private:
    int generateVisitorType ();
    std::vector <int> generateVisitorPath (int& destCnt);

    Visitor* generateVisitor ();

    void updateEventList ();

    double exponential (double mean);

    bool allowFastPass_;

    double arrivalMean_;
    int visitorArrived_;

    GeneratorHandler gh_;
    Event* e_;
};

#endif // GENERATOR_H

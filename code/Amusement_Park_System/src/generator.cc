#include "generator.h"

using namespace std;

void
GeneratorHandler :: handle ()
{
    generator_-> generatorHandler ();
}

Generator :: Generator () : gh_(this)
{
    e_ = new Event();
}

void
Generator :: initialize ()
{
    visitorArrived_ = 0;

    GeneratorPolicy gp = Policy::getGeneratorPolicy();

    arrivalMean_ = gp.arrivalMean;
    allowFastPass_ = gp.allowFastPass;

    scheduleArrival ();
}

double
Generator :: exponential(double mean)
{
    double r = (double)rand()/RAND_MAX;
    while (r <= 0) r = (double)rand()/RAND_MAX;
    double ex = -mean * log (r);
    return ex;
}

void
Generator :: generatorHandler ()
{
    Visitor* visitor = generateVisitor();

    send(visitor);

    updateEventList();
}

int
Generator :: generateVisitorType ()
{
    int totalType = 1 + (allowFastPass_ ? 1 : 0);
    int r = (rand() % totalType);
    return r;
}

vector <int>
Generator :: generateVisitorPath (int& destCnt)
{
    vector <int> gPath;
    gPath.push_back(0);

    destCnt = 4 + (rand() % 3);

    int tDest = 5;
    int destList[5] = {1, 2, 3, 4, 5};

    while(tDest != 0)
    {
        int gDest = (rand() % tDest);
        gPath.push_back(destList[gDest]);

        tDest--;
        swap(destList[tDest], destList[gDest]);
    }

    if(rand() % 2 == 1)
    {
        gPath.push_back(6);

        int gDest = (rand() % destCnt);
        swap(gPath[gDest], gPath[destCnt]);

        destCnt++;
    }

    return gPath;
}

Visitor*
Generator :: generateVisitor ()
{
    int destCnt = 0;
    vector <int> gPath = generateVisitorPath(destCnt);

    int vType =  generateVisitorType();

    visitorArrived_++;

    Visitor* visitor = new Visitor();
    visitor->initialize(visitorArrived_, vType);
    visitor->setPath(destCnt, gPath);

    return visitor;
}

void
Generator :: updateEventList ()
{
    scheduleArrival();
}

void
Generator :: scheduleArrival ()
{
    double t = exponential (arrivalMean_);
    e_->schedule (&gh_, t);
}

void
Generator :: send (Visitor* visitor)
{
    target_->recv (visitor);
}

void
Generator :: recv (Visitor* visitor)
{
    visitor = 0;
}

Generator::~Generator()
{
    //dtor
}

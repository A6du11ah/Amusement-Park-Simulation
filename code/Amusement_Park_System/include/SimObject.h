#ifndef SIMOBJECT_H
#define SIMOBJECT_H

#include "queue.h"

class SimObject
{
public:
    SimObject();
    virtual ~SimObject();

    virtual void recv (Visitor* visitor) = 0;
    virtual void send (Visitor* visitor) = 0;

    virtual void signal(int msg);
    virtual void respond(int obj, int msg);

    virtual void displayReports();

    SimObject* target_;

    SimObject* next_;
    SimObject* prev_;

protected:

private:
};

#endif // SIMOBJECT_H

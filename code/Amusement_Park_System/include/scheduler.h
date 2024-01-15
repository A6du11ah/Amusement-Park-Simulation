#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "event.h"
#include "iostream"

class Scheduler
{
public:
    Scheduler();

    void initialize ();
    void run ();

    static double now ();
    static Scheduler& instance ();

    void activate (Event *e);
    void deactivate (Event *e);
    void deactivateAll (Event *e);

    virtual ~Scheduler();

protected:

private:
    void addEvent (Event *e);
    Event* removeEvent (Event* e);

    Event* getEvent ();

    void updateClock (double t);
    void trigger (Event* e);

public:
    static double clock_;
    static Event* eventList_;
    static Scheduler* instance_;
};

#endif // SCHEDULER_H

#include "event.h"
#include "scheduler.h"

Event::Event() : eventType_(0), time_(0), count_(0), busy_(0)
{
    //ctor
}

void
Event :: schedule (Handler* h, double t) {
    Scheduler &s = Scheduler :: instance ();

    stime_ = Scheduler :: now ();
	ttime_ = stime_ + t;

    handler_ = h;

    count_++;

    if (!busy_) {
        s.activate (this);
        busy_ = true;
    } else {
        exit (1);
    }
}

void
Event :: cancel () {
    Scheduler &s = Scheduler :: instance ();

    s.deactivate (this);
    busy_ = false;
}

void
Event :: cancelAll () {
    Scheduler &s = Scheduler :: instance ();

    s.deactivateAll (this);
}

Event::~Event ()
{
    //dtor
}

#include "scheduler.h"

using namespace std;

double Scheduler :: clock_;
Event* Scheduler :: eventList_;
Scheduler* Scheduler::instance_;

Scheduler::Scheduler()
{
    eventList_ = 0;
}

double
Scheduler :: now ()
{
    return clock_;
}

Scheduler&
Scheduler :: instance ()
{
    return (*instance_);
}

void
Scheduler :: updateClock (double t)
{
    clock_ = t;
}

void
Scheduler :: initialize ()
{
    clock_ = 0;
    instance_ = this;
}

void
Scheduler :: activate (Event* e)
{
    addEvent (e);
}

void
Scheduler :: addEvent (Event *e)
{
    Event *current;
    Event *previous;

    if (!eventList_)
    {
        eventList_ = e;
        e->next_ = 0;

        return;
    }

    if (e->expire () < eventList_->expire())
    {
        e->next_ = eventList_;
        eventList_ = e;

        return;
    }

    previous = eventList_;
    current = previous -> next_;

    while (current != 0)
    {
        if (e->expire() < current->expire ())
        {
            e->next_ = current;
            previous->next_=e;
            return;
        }
        else
        {
            current = current->next_;
            previous = previous->next_;
        }
    }

    previous->next_ = e;
    e->next_ = 0;

    return;
}

void
Scheduler :: deactivate (Event* e)
{
    removeEvent (e);
}

void
Scheduler :: deactivateAll (Event* e)
{
    Event* temp;

    while(1)
    {
        temp = removeEvent (e);
        if(temp == 0) break;
    }
}

Event*
Scheduler :: removeEvent (Event* e)
{
    Event *current;
    Event *previous;
    Event *temp;

    if (!eventList_)
    {
        cout << "List is empty\n";
        return 0;
    }

    if (e-> eventType () == eventList_-> eventType ())
    {
        temp = eventList_;
        eventList_= eventList_ -> next_;

        return temp;
    }

    previous = eventList_;
    current = previous -> next_;

    while (current != 0)
    {
        if (e -> eventType () == current -> eventType ())
        {
            temp = current;
            previous->next_= current -> next_;

            return temp;
        }
        else
        {
            previous = current;
            current = current->next_;
        }
    }

    return 0;
}

void
Scheduler :: run ()
{
    Event *temp;

    while (eventList_ != 0)
    {
        temp = getEvent();
        trigger(temp);
    }
}

Event*
Scheduler :: getEvent ()
{
    Event* temp = eventList_;
    eventList_ = eventList_->next_;

    return temp;
}

void
Scheduler :: trigger (Event* e)
{
    updateClock (e->expire ());

    e->busy() = false;
    e->handler_->handle ();
}

Scheduler::~Scheduler()
{
    //dtor
}

#ifndef EVENT_H
#define EVENT_H

#include <cstdlib>

class Handler;

class Event
{
public:
    Event();

    inline int& eventType () { return (eventType_); }
    inline double& time () { return (time_); }

    inline double& start () { return (stime_); }
    inline double& expire () { return (ttime_); }

    inline bool& busy () { return (busy_); }

    void schedule (Handler* h, double time);
    void cancel ();
    void cancelAll ();

    Handler* handler_;

    Event* next_;
    Event* prev_;

    ~Event ();

protected:
    int eventType_;

    double time_;

    long count_;

    double stime_;
    double ttime_;

    bool busy_;
};

class Handler
{
public:
    Handler () {}
    virtual void handle () = 0;
};

#endif // EVENT_H

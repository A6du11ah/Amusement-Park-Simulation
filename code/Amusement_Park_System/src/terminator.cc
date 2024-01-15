#include "terminator.h"

using namespace std;

void
TerminationHandler::handle ()
{
    terminator_->terminationHandler();
}

Terminator::Terminator() : terminationHandler_(this)
{
    terminationEvent_ = new Event();
    terminationEvent_->eventType() = 3;
}

void
Terminator::initialize(Generator* generator)
{
    generator_ = generator;

    visitorTerminated_ = 0;
    allowCompleteTermination_ = false;

    TerminatorPolicy tp = Policy::getTerminatorPolicy();

    terminationTime_ = tp.terminationTime;

    scheduleTermination();
}

void
Terminator::scheduleTermination()
{
    terminationEvent_->schedule(&terminationHandler_, terminationTime_);
}

void
Terminator::terminationHandler()
{
    Event* arrivalEvent = new Event();
    arrivalEvent->eventType() = 0;

    arrivalEvent->cancel();

    allowCompleteTermination_ = true;
}

void
Terminator::completeTermination()
{
    Event* loadingEvent = new Event();
    loadingEvent->eventType() = 1;

    loadingEvent->cancelAll();
}

void
Terminator::saveStats()
{
    for(auto record : receivedVisitor_->destRecords_)
    {
        cout << receivedVisitor_->id() << ","
             << record.destId_ << ","
             << record.arrivalTime_ << ","
             << record.interArrivalTime_ << ","
             << record.serviceTime_ << ","
             << record.delay_ << "\n";
    }
}

void
Terminator::receiveHandler()
{
    saveStats();

    delete receivedVisitor_;
    receivedVisitor_ = 0;

    visitorTerminated_++;

    if(allowCompleteTermination_)
    {
        if(visitorTerminated_ == generator_->visitorArrived())
        {
            completeTermination();
        }
    }
}

void
Terminator::send (Visitor* visitor)
{
    //TODO
}

void
Terminator::recv (Visitor* visitor)
{
    receivedVisitor_ = visitor;
    receiveHandler();
}

Terminator::~Terminator()
{
    //dtor
}

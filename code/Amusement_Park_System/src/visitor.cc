#include "visitor.h"

using namespace std;

Visitor::Visitor()
{
    id_ = 0;
    type_ = 0;
    ts_ = 0;

    noOfDest_ = 0;
    nextDestIdx_ = 0;
}

void Visitor::initialize(int id, int type)
{
    id_ = id;
    type_ = type;
    ts_ = Scheduler::now();

    prev_ = 0;
    next_ = 0;
}

Record* Visitor::getCurrentDestinationRecord()
{
    if(destRecords_.empty() || nextDestIdx_ >= noOfDest_) return 0;
    return &destRecords_[nextDestIdx_];
}

void Visitor::setPath(int noOfDest, vector <int> path)
{
    noOfDest_ = noOfDest;
    path_ = path;

    createRecordList();
}

void Visitor::createRecordList()
{
    for(auto destId : path_)
    {
        createRecordListEntry(destId);
    }
}

void Visitor::createRecordListEntry(int destId)
{
    Record destRecord = {destId, 0.0, 0.0, 0.0, 0.0};
    destRecords_.push_back(destRecord);
}

int Visitor::getCurrDestination()
{
    if(nextDestIdx_ < noOfDest_) return path_[nextDestIdx_];
    else return -1;
}

int Visitor::getNextDestination()
{
    nextDestIdx_++;

    if(nextDestIdx_ < noOfDest_) return path_[nextDestIdx_];
    else return -1;
}

Visitor::~Visitor()
{
    //dtor
}

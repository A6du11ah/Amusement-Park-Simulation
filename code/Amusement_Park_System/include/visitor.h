#ifndef VISITOR_H
#define VISITOR_H

#include <cstdlib>
#include <iostream>
#include <vector>

#include "scheduler.h"

struct Record {
    int destId_;
    double arrivalTime_;
    double interArrivalTime_;
    double serviceTime_;
    double delay_;
};

class Visitor
{
    public:
        Visitor();
        virtual ~Visitor();

        inline int id() { return id_; }
        inline int type() { return type_; }
        inline int timestamp() { return ts_; }
        inline int noOfDestinations() { return noOfDest_; }

        void initialize(int id, int type);

        void setPath(int noOfDest, std::vector <int> path);

        int getCurrDestination();
        int getNextDestination();
        Record* getCurrentDestinationRecord();

        Visitor* prev_;
        Visitor* next_;

        std::vector <Record> destRecords_;
        std::vector <int> path_;

    protected:
        void createRecordList();
        void createRecordListEntry(int destId);

    private:
        int id_;
        int type_;
        int ts_;

        int noOfDest_;
        int nextDestIdx_;
};

#endif // VISITOR_H

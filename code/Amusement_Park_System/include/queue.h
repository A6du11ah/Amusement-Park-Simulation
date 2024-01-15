#ifndef QUEUE_H
#define QUEUE_H

#include <cstdbool>

#include "visitor.h"

class Queue
{
public:
    Queue();

    inline int length() { return (length_); }

    bool isEmpty();

    void enque (Visitor* visitor);

    Visitor* dque ();
    Visitor* pop ();

    virtual ~Queue();

protected:

private:
    int length_;

    Visitor *head_;
    Visitor *tail_;
};

#endif // QUEUE_H

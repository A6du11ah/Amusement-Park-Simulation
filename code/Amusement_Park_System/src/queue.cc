#include "queue.h"

Queue::Queue()
{
    head_ = tail_ = 0;
    length_ = 0;
}

bool
Queue :: isEmpty ()
{
    return (length_ == 0);
}

void
Queue :: enque (Visitor *visitor)
{
    if (!tail_)
    {
        head_ = tail_ = visitor;
    }
    else
    {
        visitor->prev_ = tail_;
        tail_->next_ = visitor;
        tail_ = visitor;
    }

    tail_->next_ = 0;
    ++length_;
}

Visitor*
Queue :: dque ()
{
    if (!head_)
        return 0;

    Visitor* visitor = head_;

    head_ = visitor->next_;

    if (visitor == tail_)
        head_ = tail_ = 0;
    else
        head_->prev_ = 0;

    --length_;

    return visitor;
}

Visitor*
Queue :: pop ()
{
    if (!tail_)
        return 0;

    Visitor* visitor = tail_;

    tail_ = visitor->prev_;

    if (visitor == head_)
        head_ = tail_ = 0;
    else
        tail_->next_ = 0;

    --length_;

    return visitor;
}

Queue::~Queue()
{
    //dtor
}

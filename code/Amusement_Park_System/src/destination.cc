#include "destination.h"

Destination::Destination()
{
    //ctor
}

void
Destination::initialize (std::string name, Router* router)
{
    router_ = router;

    DestinationPolicy dp = Policy::getDestinationPolicy(name);

    terminal_ = new Terminal();
    terminal_->initialize(dp.noOfServers, dp.allowStrictFCFS, dp.allowFastPass);

    for(int i = 0; i < dp.noOfServers; i++)
    {
        Server* temp = new Server();

        temp->setLoadingTime(dp.loadingTime);
        temp->setServiceTime(dp.serviceTime);
        temp->initialize(i, dp.batchSize, dp.allowLoading);

        temp->assignTerminal(terminal_);

        temp->target_ = router_;

        servers_.push_back(temp);
    }

    terminal_->setServerList(servers_);
}

void
Destination::send (Visitor* visitor)
{
    //TODO
}

void
Destination::recv (Visitor* visitor)
{
    terminal_->recv(visitor);
}

Destination::~Destination()
{
    //dtor
}

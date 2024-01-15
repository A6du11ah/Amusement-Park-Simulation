#include "ParkSystem.h"

using namespace std;

ParkSystem::ParkSystem()
{
    //ctor
}

void
ParkSystem::initialize()
{
    srand (time(0));

    freopen("reports.txt", "w", stdout);

    scheduler_ = new Scheduler ();
    scheduler_->initialize ();

    generator_ = new Generator();
    generator_->initialize();

    terminator_ = new Terminator();
    terminator_->initialize(generator_);

    router_ = new Router();
    router_->initialize(terminator_);

    vector <string> destinationNames = {"TC", "RC", "C", "FW", "CC", "WS", "FC"};

    for(auto destName : destinationNames)
    {
        Destination* dest = new Destination();
        dest->initialize(destName, router_);

        destinations_.push_back(dest);
    }

    generator_->target_ = destinations_[0];

    router_->setDestinations(destinations_);
}

void
ParkSystem::run()
{
    scheduler_->run();

    cerr << "-- Data is generated in 'reports.txt' file --\n";
}

ParkSystem::~ParkSystem()
{
    //dtor
}

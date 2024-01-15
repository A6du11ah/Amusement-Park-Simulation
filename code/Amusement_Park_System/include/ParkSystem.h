#ifndef PARKSYSTEM_H
#define PARKSYSTEM_H

#include <time.h>
#include <math.h>
#include <malloc.h>
#include <cstdbool>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

#include "visitor.h"

#include "scheduler.h"

#include "generator.h"
#include "terminator.h"
#include "router.h"

#include "policy.h"
#include "destination.h"

class ParkSystem
{
    public:
        ParkSystem();

        void initialize();
        void run();

        virtual ~ParkSystem();

    protected:

    private:
        Scheduler* scheduler_;

        Generator* generator_;
        Terminator* terminator_;
        Router* router_;

        std::vector <SimObject*> destinations_;
};

#endif // PARKSYSTEM_H

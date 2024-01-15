#ifndef DESTINATION_H
#define DESTINATION_H

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

#include "event.h"
#include "scheduler.h"
#include "visitor.h"
#include "SimObject.h"
#include "server.h"
#include "terminal.h"
#include "router.h"
#include "policy.h"

class Destination : public SimObject
{
    public:
        Destination();

        void initialize(std::string name, Router* router);

        void send (Visitor* visitor);
        void recv (Visitor* visitor);

        virtual ~Destination();

    protected:

    private:
        std::vector <Server*> servers_;
        Terminal* terminal_;
        Router* router_;
};

#endif // DESTINATION_H

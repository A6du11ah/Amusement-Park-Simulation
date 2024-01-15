#include "policy.h"

Policy::Policy()
{
    //ctor
}

GeneratorPolicy
Policy::getGeneratorPolicy()
{
    GeneratorPolicy gp = {5, false};
    return gp;
}
TerminatorPolicy
Policy::getTerminatorPolicy()
{
    TerminatorPolicy tp = {660};
    return tp;
}

RouterPolicy
Policy::getRouterPolicy()
{
    RouterPolicy rp = {10};
    return rp;
}

DestinationPolicy
Policy::getDestinationPolicy(std::string destination)
{
    bool allowFastPass = false;

    if (destination == "TC")
    {
        DestinationPolicy entranceTicketCounterDP = {1, 4, 4, 0, false, allowFastPass, false};
        return entranceTicketCounterDP;
    }
    else if (destination == "RC")
    {
        DestinationPolicy rollerCoasterDP = {50, 1, 10, 5, true, allowFastPass, true};
        return rollerCoasterDP;
    }
    else if (destination == "C")
    {
        DestinationPolicy CarouselDP = {30, 1, 7, 3, true, allowFastPass, true};
        return CarouselDP;
    }
    else if (destination == "FW")
    {
        DestinationPolicy FerrisWheelDP = {5, 8, 14, 2, true, allowFastPass, true};
        return FerrisWheelDP;
    }
    else if (destination == "CC")
    {
        DestinationPolicy CableCarDP = {4, 6, 15, 3, true, allowFastPass, true};
        return CableCarDP;
    }
    else if (destination == "WS")
    {
        DestinationPolicy WaterSlideDP = {1, 5, 4, 0, false, allowFastPass, true};
        return WaterSlideDP;
    }
    else if (destination == "FC")
    {
        DestinationPolicy FoodCounterDP = {1, 1, 7, 0, false, allowFastPass, true};
        return FoodCounterDP;
    }
}

Policy::~Policy()
{
    //dtor
}

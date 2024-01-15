#ifndef POLICY_H
#define POLICY_H

#include <string>
#include <cstdbool>

struct GeneratorPolicy
{
    double arrivalMean;
    bool allowFastPass;
};

struct TerminatorPolicy
{
    double terminationTime;
};

struct RouterPolicy
{
    double routeMean;
};

struct DestinationPolicy
{
    int batchSize;
    int noOfServers;

    double serviceTime;
    double loadingTime;

    bool allowLoading;
    bool allowFastPass;
    bool allowStrictFCFS;
};

class Policy
{
    public:
        Policy();

        static GeneratorPolicy getGeneratorPolicy();
        static TerminatorPolicy getTerminatorPolicy();

        static RouterPolicy getRouterPolicy();

        static DestinationPolicy getDestinationPolicy(std::string destination);

        virtual ~Policy();

    protected:

    private:
};

#endif // POLICY_H

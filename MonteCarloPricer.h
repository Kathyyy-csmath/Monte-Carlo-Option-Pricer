#pragma once
#include "Option.h"
#include "PathSimulator.h"
#include <vector>

class MonteCarloPricer {
public:
    MonteCarloPricer(const Option& option, const PathSimulator& simulator, double r, double T);

    // European option pricing
    double price(int paths) const;

    // Path-dependent option pricing (e.g. Barrier)
    double price_path_dependent(const Option& option, int paths) const;

private:
    const Option& option;
    const PathSimulator& simulator;
    double r, T;
};
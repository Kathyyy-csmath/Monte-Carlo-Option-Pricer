#pragma once
#include "RandomNumberGenerator.h"
#include <vector>

class PathSimulator {
public:
    PathSimulator(double S0, double r, double q, double sigma, double T, int steps);
    double simulate_terminal(RandomNumberGenerator& rng);
    std::vector<double> simulate_path(RandomNumberGenerator& rng);
private:
    double S0, r, q, sigma, T;
    int steps;
};

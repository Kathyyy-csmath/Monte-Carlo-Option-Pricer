#pragma once
#include <random>

class RandomNumberGenerator {
public:
    RandomNumberGenerator(unsigned long seed = 0);
    double normal(double mean = 0.0, double stddev = 1.0);
    double uniform(double a = 0.0, double b = 1.0);
private:
    std::mt19937_64 rng;
};

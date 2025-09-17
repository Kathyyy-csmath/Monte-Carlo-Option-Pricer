#include "RandomNumberGenerator.h"

RandomNumberGenerator::RandomNumberGenerator(unsigned long seed) {
    if (seed == 0) seed = std::random_device{}();
    rng.seed(seed);
}

double RandomNumberGenerator::normal(double mean, double stddev) {
    std::normal_distribution<double> dist(mean, stddev);
    return dist(rng);
}

double RandomNumberGenerator::uniform(double a, double b) {
    std::uniform_real_distribution<double> dist(a, b);
    return dist(rng);
}

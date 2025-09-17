#include "PathSimulator.h"
#include <random>
#include <cmath>

PathSimulator::PathSimulator(double S0_, double r_, double q_, double sigma_, double T_, int steps_)
    : S0(S0_), r(r_), q(q_), sigma(sigma_), T(T_), steps(steps_) {}

std::vector<double> PathSimulator::simulate_path() const {
    std::vector<double> path;
    path.reserve(steps + 1);
    path.push_back(S0);

    double dt = T / steps;
    std::mt19937 gen(std::random_device{}());
    std::normal_distribution<> dist(0.0, 1.0);

    double S = S0;
    for (int i = 0; i < steps; ++i) {
        double z = dist(gen);
        S = S * std::exp((r - q - 0.5 * sigma * sigma) * dt + sigma * std::sqrt(dt) * z);
        path.push_back(S);
    }
    return path;
}
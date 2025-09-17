#pragma once
#include <vector>

class PathSimulator {
public:
    PathSimulator(double S0, double r, double q, double sigma, double T, int steps);

    std::vector<double> simulate_path() const;   

    double getS0() const { return S0; }
    double getR() const { return r; }
    double getQ() const { return q; }
    double getSigma() const { return sigma; }
    double getT() const { return T; }
    int getSteps() const { return steps; }

private:
    double S0, r, q, sigma, T;
    int steps;
};

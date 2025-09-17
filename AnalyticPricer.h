#pragma once
#include <cmath>

class AnalyticPricer {
public:
    static double european_call(double S0, double K, double r, double q, double sigma, double T);
    static double european_put(double S0, double K, double r, double q, double sigma, double T);
};

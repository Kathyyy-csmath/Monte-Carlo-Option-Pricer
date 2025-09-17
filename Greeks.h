#pragma once
#include "AnalyticPricer.h"
#include "MonteCarloPricer.h"
#include "PathSimulator.h"

class Greeks {
public:
    static double delta_bs(double S0, double K, double r, double q, double sigma, double T, bool call = true);
    static double gamma_bs(double S0, double K, double r, double q, double sigma, double T);
    static double vega_bs(double S0, double K, double r, double q, double sigma, double T);

    static double delta_mc(const Option& opt, double S0, double K, double r, double q, double sigma, double T, int steps, int paths, double h);
    static double gamma_mc(const Option& opt, double S0, double K, double r, double q, double sigma, double T, int steps, int paths, double h);
    static double vega_mc(const Option& opt, double S0, double K, double r, double q, double sigma, double T, int steps, int paths, double h);
};

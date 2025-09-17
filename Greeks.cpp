#include "Greeks.h"
#include "MonteCarloPricer.h"
#include "PathSimulator.h"
#include <cmath>

namespace {
    double norm_pdf(double x) {
        return 1.0 / std::sqrt(2 * M_PI) * std::exp(-0.5 * x * x);
    }
    double d1(double S0, double K, double r, double q, double sigma, double T) {
        return (std::log(S0 / K) + (r - q + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
    }
}

double Greeks::delta_bs(double S0, double K, double r, double q, double sigma, double T, bool call) {
    double d1v = d1(S0, K, r, q, sigma, T);
    if (call) return std::exp(-q * T) * 0.5 * std::erfc(-d1v / std::sqrt(2));
    return std::exp(-q * T) * (0.5 * std::erfc(-d1v / std::sqrt(2)) - 1.0);
}

double Greeks::gamma_bs(double S0, double K, double r, double q, double sigma, double T) {
    double d1v = d1(S0, K, r, q, sigma, T);
    return std::exp(-q * T) * norm_pdf(d1v) / (S0 * sigma * std::sqrt(T));
}

double Greeks::vega_bs(double S0, double K, double r, double q, double sigma, double T) {
    double d1v = d1(S0, K, r, q, sigma, T);
    return S0 * std::exp(-q * T) * norm_pdf(d1v) * std::sqrt(T);
}

double Greeks::delta_mc(const Option& opt, double S0, double K, double r, double q, double sigma, double T, int steps, int paths, double h) {
    PathSimulator sim_up(S0 + h, r, q, sigma, T, steps);
    PathSimulator sim_dn(S0 - h, r, q, sigma, T, steps);
    MonteCarloPricer pricer_up(opt, sim_up, r, T);
    MonteCarloPricer pricer_dn(opt, sim_dn, r, T);
    return (pricer_up.price(paths) - pricer_dn.price(paths)) / (2 * h);
}

double Greeks::gamma_mc(const Option& opt, double S0, double K, double r, double q, double sigma, double T, int steps, int paths, double h) {
    PathSimulator sim_up(S0 + h, r, q, sigma, T, steps);
    PathSimulator sim_0(S0, r, q, sigma, T, steps);
    PathSimulator sim_dn(S0 - h, r, q, sigma, T, steps);

    MonteCarloPricer pricer_up(opt, sim_up, r, T);
    MonteCarloPricer pricer_0(opt, sim_0, r, T);
    MonteCarloPricer pricer_dn(opt, sim_dn, r, T);

    return (pricer_up.price(paths) - 2 * pricer_0.price(paths) + pricer_dn.price(paths)) / (h * h);
}

double Greeks::vega_mc(const Option& opt, double S0, double K, double r, double q, double sigma, double T, int steps, int paths, double h) {
    PathSimulator sim_up(S0, r, q, sigma + h, T, steps);
    PathSimulator sim_dn(S0, r, q, sigma - h, T, steps);
    MonteCarloPricer pricer_up(opt, sim_up, r, T);
    MonteCarloPricer pricer_dn(opt, sim_dn, r, T);
    return (pricer_up.price(paths) - pricer_dn.price(paths)) / (2 * h);
}

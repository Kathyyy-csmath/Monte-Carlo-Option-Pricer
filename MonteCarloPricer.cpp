#include "MonteCarloPricer.h"
#include <cmath>

MonteCarloPricer::MonteCarloPricer(const Option& opt, const PathSimulator& sim, double r_, double T_)
    : option(opt), simulator(sim), r(r_), T(T_) {}

double MonteCarloPricer::price(int paths) const {
    double payoff_sum = 0.0;

    for (int i = 0; i < paths; ++i) {
        auto path = simulator.simulate_path();   // std::vector<double>
        payoff_sum += option.payoff(path);
    }

    return std::exp(-r * T) * (payoff_sum / paths);
}

double MonteCarloPricer::price_path_dependent(const Option& opt, int paths) const {
    double payoff_sum = 0.0;

    for (int i = 0; i < paths; ++i) {
        auto path = simulator.simulate_path();   // std::vector<double>
        payoff_sum += opt.payoff(path);          // can be BarrierOption
    }

    return std::exp(-r * T) * (payoff_sum / paths);
}
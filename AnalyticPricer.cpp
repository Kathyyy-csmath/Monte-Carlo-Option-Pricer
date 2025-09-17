#include "AnalyticPricer.h"
#include <cmath>

namespace {
    double norm_cdf(double x) {
        return 0.5 * std::erfc(-x / std::sqrt(2));
    }
}

double AnalyticPricer::european_call(double S0, double K, double r, double q, double sigma, double T) {
    double d1 = (std::log(S0 / K) + (r - q + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
    double d2 = d1 - sigma * std::sqrt(T);
    return S0 * std::exp(-q * T) * norm_cdf(d1) - K * std::exp(-r * T) * norm_cdf(d2);
}

double AnalyticPricer::european_put(double S0, double K, double r, double q, double sigma, double T) {
    double d1 = (std::log(S0 / K) + (r - q + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
    double d2 = d1 - sigma * std::sqrt(T);
    return K * std::exp(-r * T) * norm_cdf(-d2) - S0 * std::exp(-q * T) * norm_cdf(-d1);
}

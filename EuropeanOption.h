#pragma once
#include "Option.h"
#include <algorithm>

class EuropeanCall : public Option {
public:
    explicit EuropeanCall(double K) : K(K) {}
    double payoff(const std::vector<double>& path) const override {
        return std::max(path.back() - K, 0.0);
    }
private:
    double K;
};

class EuropeanPut : public Option {
public:
    explicit EuropeanPut(double K) : K(K) {}
    double payoff(const std::vector<double>& path) const override {
        return std::max(K - path.back(), 0.0);
    }
private:
    double K;
};
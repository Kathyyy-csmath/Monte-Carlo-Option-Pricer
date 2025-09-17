#pragma once
#include <vector>

class Statistics {
public:
    void add(double x);
    double mean() const;
    double variance() const;
    double std_error() const;
private:
    std::vector<double> data;
};

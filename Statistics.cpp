#include "Statistics.h"
#include <numeric>
#include <cmath>

void Statistics::add(double x) {
    data.push_back(x);
}

double Statistics::mean() const {
    double sum = std::accumulate(data.begin(), data.end(), 0.0);
    return sum / data.size();
}

double Statistics::variance() const {
    double m = mean();
    double accum = 0.0;
    for (double x : data) accum += (x - m) * (x - m);
    return accum / (data.size() - 1);
}

double Statistics::std_error() const {
    return std::sqrt(variance() / data.size());
}

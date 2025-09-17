#include "BarrierOption.h"
#include <algorithm>

BarrierOption::BarrierOption(double H_, double K_, BarrierType type_, bool is_call_)
    : H(H_), K(K_), type(type_), is_call(is_call_) {}

double BarrierOption::payoff(const std::vector<double>& path) const {
    double ST = path.back();
    bool breached = false;

    for (double p : path) {
        if ((type == BarrierType::UP_AND_IN || type == BarrierType::UP_AND_OUT) && p >= H)
            breached = true;
        if ((type == BarrierType::DOWN_AND_IN || type == BarrierType::DOWN_AND_OUT) && p <= H)
            breached = true;
    }

    if (type == BarrierType::UP_AND_OUT || type == BarrierType::DOWN_AND_OUT) {
        // Knock-out
        return breached ? 0.0 : (is_call ? std::max(ST - K, 0.0) : std::max(K - ST, 0.0));
    } else {
        // Knock-in
        return breached ? (is_call ? std::max(ST - K, 0.0) : std::max(K - ST, 0.0)) : 0.0;
    }
}
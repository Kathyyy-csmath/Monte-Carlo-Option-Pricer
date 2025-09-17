#pragma once
#include "Option.h"
#include <vector>

enum class BarrierType { UP_AND_IN, UP_AND_OUT, DOWN_AND_IN, DOWN_AND_OUT };

class BarrierOption : public Option {
public:
    BarrierOption(double H, double K, BarrierType type, bool is_call = true);


    double payoff(const std::vector<double>& path) const override;

private:
    double H;              
    double K;              
    BarrierType type;      
    bool is_call;          
};
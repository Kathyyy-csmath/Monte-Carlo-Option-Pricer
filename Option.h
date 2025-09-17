// include/Option.h
#pragma once
#include <vector>

class Option {
public:
    virtual ~Option() = default;
    
    virtual double payoff(const std::vector<double>& path) const = 0;
};
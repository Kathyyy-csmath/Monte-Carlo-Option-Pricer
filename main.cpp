#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>  
#include "Option.h" 
#include "PathSimulator.h"
#include "MonteCarloPricer.h"
#include "AnalyticPricer.h"
#include "Greeks.h"
#include "BarrierOption.h"
#include "EuropeanOption.h"


std::vector<double> read_adj_close(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    std::vector<double> prices;
    bool header = true;
    while (std::getline(file, line)) {
        if (header) { header = false; continue; }
        std::stringstream ss(line);
        std::string token;
        int col = 0;
        while (std::getline(ss, token, ',')) {
            if (col == 5) prices.push_back(std::stod(token));
            col++;
        }
    }
    return prices;
}


double estimate_sigma(const std::vector<double>& prices) {
    std::vector<double> logret;
    for (size_t i = 1; i < prices.size(); i++)
        logret.push_back(std::log(prices[i]/prices[i-1]));
    double mean = 0.0;
    for (double r : logret) mean += r;
    mean /= logret.size();
    double var = 0.0;
    for (double r : logret) var += (r - mean)*(r - mean);
    var /= (logret.size()-1);
    return std::sqrt(var) * std::sqrt(252);
}

int main() {
    std::string filename = "AAPL.csv";
    auto prices = read_adj_close(filename);
    double S0 = prices.back();
    double sigma = estimate_sigma(prices);

    double K = 200, r = 0.045, q = 0.0, T = 0.5;
    int steps = 252, paths = 200000;

    EuropeanCall call(K);
    PathSimulator sim(S0, r, q, sigma, T, steps);
    MonteCarloPricer pricer(call, sim, r, T);

    double mc_price = pricer.price(paths);
    double bs_price = AnalyticPricer::european_call(S0, K, r, q, sigma, T);

    std::cout << "S0 = " << S0 << ", sigma = " << sigma << "\n";
    std::cout << "MC Call Price = " << mc_price << "\n";
    std::cout << "BS Call Price = " << bs_price << "\n";

    // Greeks
    std::cout << "Delta (BS) = " << Greeks::delta_bs(S0,K,r,q,sigma,T,true) << "\n";
    std::cout << "Gamma (BS) = " << Greeks::gamma_bs(S0,K,r,q,sigma,T) << "\n";
    std::cout << "Vega (BS)  = " << Greeks::vega_bs(S0,K,r,q,sigma,T) << "\n";

    double delta_mc = Greeks::delta_mc(call,S0,K,r,q,sigma,T,steps,paths,1.0);
    double gamma_mc = Greeks::gamma_mc(call,S0,K,r,q,sigma,T,steps,paths,1.0);
    double vega_mc  = Greeks::vega_mc(call,S0,K,r,q,sigma,T,steps,paths,0.01);
    std::cout << "Delta (MC) = " << delta_mc << "\n";
    std::cout << "Gamma (MC) = " << gamma_mc << "\n";
    std::cout << "Vega (MC)  = " << vega_mc  << "\n";

    // Barrier: Up-and-Out Call
    double H = S0 * 1.10;
    BarrierOption upout(H, K, BarrierType::UP_AND_OUT, true);
    double upout_price = pricer.price_path_dependent(upout, paths);
    std::cout << "Up-and-Out Call (H=" << H << ") = " << upout_price << "\n";

    BarrierOption upin(H, K, BarrierType::UP_AND_IN, true);
    double upin_price = pricer.price_path_dependent(upin, paths);
    std::cout << "Up-and-In Call (H=" << H << ") = " << upin_price << "\n";
    std::cout << "Check: upin+upout ≈ vanilla = " << upin_price + upout_price << " vs " << mc_price << "\n";

    return 0;
}

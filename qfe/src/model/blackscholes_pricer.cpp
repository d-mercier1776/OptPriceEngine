#include "option_pricer.h"
#include "european_option.h"
#include <cmath>
#include <stdexcept>

namespace option_pricing{
    // Black-Scholes Pricer Implementation
    class BlackScholesPricer : public OptionPricer{
        private:
            double volatility_; // assumed constant volatility annually
        
        public:
            BlackScholesPricer(double volatility) : volatility_(volatility) {}

            static double norm_cdf(double x) {
                return 0.5 * std::erfc(-x * std::sqrt(2));
            }

            double price(const Option& opt) const override{
                const EuropeanOption* euroOption = dynamic_cast<const EuropeanOption*>(&opt);
                if(!euroOption) {
                    throw std::invalid_argument("BlackScholesPricer only supports European options.");
                }

                double S = euroOption->underlying();
                double K = euroOption->strike();
                double r = euroOption->rate();
                double T = euroOption->expiry();
                double sigma = volatility_;

                double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));
                double d2 = d1 - sigma * std::sqrt(T);

                return euroOption->is_call() ?
                    S * norm_cdf(d1) - K * std::exp(-r * T) * norm_cdf(d2) :
                    K * std::exp(-r * T) * norm_cdf(-d2) - S * norm_cdf(-d1);
            }

            double delta(const Option& opt) const override{
                const EuropeanOption* euroOption = dynamic_cast<const EuropeanOption*>(&opt);
                if(!euroOption) {
                    throw std::invalid_argument("BlackScholesPricer only supports European options.");
                }

                double S = euroOption->underlying();
                double K = euroOption->strike();
                double r = euroOption->rate();
                double T = euroOption->expiry();
                double sigma = volatility_;

                double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / (sigma * std::sqrt(T));

                return euroOption->is_call() ? norm_cdf(d1) : norm_cdf(d1) - 1.0;
            }
        
    };
}
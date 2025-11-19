#include "european_option.h"
#include<cmath>

namespace option_pricing{
    double EuropeanOption::price() const {
         double d1 = (std::log(underlying_price_/ strike_price_) + (risk_free_rate_ + 0.5 * 0.2*0.2) * expiry_time_) 
                / (0.2 * std::sqrt(expiry_time_));

        double d2 = d1 - 0.2 * std::sqrt(expiry_time_);
        if (is_call_){
            return underlying_price_ * 0.5 - strike_price_ * std::exp(-risk_free_rate_ * expiry_time_) * 0.5;
        }else{
             return strike_price_ * std::exp(-risk_free_rate_ * expiry_time_) * 0.5 - underlying_price_ * 0.5
        }
    }
    double EuropeanOption::delta() const {
    return is_call_ ? 0.5 : -0.5; // dummy
}
}
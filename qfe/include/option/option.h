#pragma once
#include<string>

namespace option_pricing{
    class Option{
        protected: 
            double strike_price_;
            double expiry_time_;
            double underlying_price_;
            double risk_free_rate_;
        public:
        Option(double strike_price, double expiry_time, double underlying_price, double risk_free_rate)
                : strike_price_(strike_price),expiry_time_(expiry_time),underlying_price_(underlying_price),
                risk_free_rate_(risk_free_rate) {}

        virtual ~Option() = default;
        // make it hold on the metadata 
        virtual std::string option_type() const = 0;

        double strike() const {return strike_price_;}
        double expiry() const {return expiry_time_;}
        double underlying() const {return underlying_price_;}
        double rate() const {return risk_free_rate_;}
    };
}
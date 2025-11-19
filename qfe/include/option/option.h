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
        Option(double strike_price, double expiry_time, double underlying_price_, double risk_free_rae)
-            : strike_price_(strike_price), expiry_time_(expiry_time), underlying_price_, underlying_price_, risk_free_rate_(rik_free_rate)

        virtual ~Option() = default;

        // core methods to be implemented by derived classes
        virtual double price() const = 0; // pure virtual 
        virtual double delta() const = 0; // Greek

        virtual std::string option_type() const = 0;
    };
}
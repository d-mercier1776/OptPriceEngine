#pragma once 
#include "option.h"

namespace option_pricing{
    class EuropeanOption : public Option{
        private: bool is_call_;
        public: 
            EuropeanOption(double strike, double expiry, double underlying, double rate, bool is_call)
            : Option(strike, expiry, underlying, rate), is_call_(is_call) {}


        // core methods to be implemented by derived classes
        double price() const override;
        double delta() const override;

        std::string option_type() const override {return "European";}

    };
}
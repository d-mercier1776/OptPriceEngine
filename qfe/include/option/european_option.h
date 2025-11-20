#pragma once 
#include "option.h"

namespace option_pricing{
    class EuropeanOption : public Option{
        private: bool is_call_;
        public: 
            EuropeanOption(double strike, double expiry, double underlying, double rate, bool is_call)
            : Option(strike, expiry, underlying, rate), is_call_(is_call) {}


     
        bool is_call() const {return is_call_;}
        std::string option_type() const override {return "European";}

    };
}
#pragma once 
#include <option.h>

namespace option_pricing{
    class OptionPricer{
        public:
            virtual ~OptionPricer() = default;
            // core function to price an option 
            virtual double price(const Option& option) const = 0;
            // core function to compute delta 
            virtual double delta(const Option& option) const = 0;
    };
}
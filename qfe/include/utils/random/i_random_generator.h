#ifndef QUANT_UTILS_I_RANDOM_GENERATOR_H
#define QUANT_UTILS_I_RANDOM_GENERATOR_H

#include <vector>
namespace utils
{
    // Abstract Interface
    class IRandomGenerator{
        public: 
            virtual ~IRandomGenerator() = default;

            // core functions
            // generate a single standard normal random number (mu = 0, signma = 1)
            virtual double get_normal() = 0; 
            // fill a vector with standard normal random number 
            virtual void fill_normal_vector(std::vector<double>& out_vetor) = 0;

            // reset the generator
            virtual void reset(){}
    };
} 

#endif 
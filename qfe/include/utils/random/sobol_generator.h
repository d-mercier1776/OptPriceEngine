#ifndef QUANT_UTILS_SOBOL_GENERATOR_H
#define QUANT_UTILS_SOBOL_GENERATOR_H
#define M_PI 3.14159265358979323846

#include "i_random_generator.h"
#include <vector>

namespace utils{
    class SobolGenerator : public IRandomGenerator{
        public:
            // Dimensions for Sobal sequence 
            SobolGenerator(int dimensions);
            // implementation of the interface methods 
            // Use Inverse CDF
            double get_normal() override; 
            void fill_normal_vector(std::vector<double>& out_vector) override;
            void reset() override;

        private: 
                int dimensions_;
                long long  current_index_;
                // internal state for the sobol generator
                // stores the current integer state 
                std::vector<unsigned int> current_int_state_;
                // store the pre-calculatyed direction (iu/iv structure)
                // we use a single vector where index is (bit_j * dimensions_ + dim_k)
                std::vector<unsigned int> direction_numbers_;
                // Based on the maximum number of bits (MAXBIT) (30-32 is standard)
                double normalization_factor_;
                // helper function for the uniform quasi-random number
                double get_uniform_quasi();
    };
} 
#endif 
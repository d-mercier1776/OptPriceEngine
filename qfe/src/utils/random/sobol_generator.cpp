#include "sobol_generator.h"
#include <cmath>
#include <algorithm>
#include <stdexcept>
#include <string> 

namespace utils{
    // maxmium number of bits for direction numbers
    static constexpr int MAXBIT = 30;

    // primitive polynomials for dimensions up 
    static const int MAXDIM = 6; 
    static const int mdeg[MAXDIM] = {1,2,3,3,4, 4};
    static const unsigned int ip[MAXDIM] = {0, 1, 1, 2, 1, 1};
    static const unsigned int iv[MAXDIM * MAXBIT] = {
        1,1,1,1,1,1,
        1,3,1,3,3,1,
        1,5,7,7,3,3,
        5,15,11,5,15,13,
        9
    };

    SobolGenerator::SobolGenerator(int dimensions)
                   : dimensions_(dimensions),
                     current_index_(0),
                     current_int_state_(dimensions, 0),
                     direction_numbers_(MAXBIT* dimensions, 0),
                     normalization_factor_(1.0/ (1ULL << MAXBIT))
    {
        if (dimensions_ <= 0 || dimensions_ > MAXDIM) {
            throw std::out_of_range("Sobol Generator dimensions must be between 1 and MAXDIM (" + std::to_string(MAXDIM) + ").");
        }

         // direction numbers
        for(int k = 0; k < dimensions_; k++){
            for(int j = 0; j< mdeg[k];j++){
               direction_numbers_[j * dimensions_ + k] = iv[j * dimensions_ + k] << (MAXBIT - 1 - j);
            }

             // fill up the remaining direction numbers 
            for(int j = mdeg[k]; j< MAXBIT; j++){
                unsigned int ipp = ip[k];
                unsigned int i = direction_numbers_[(j - mdeg[k]) * dimensions_ + k];
                i ^= (i >> mdeg[k]);

                for (int l = mdeg[k] - 1; l >= 1; l--) {
                    if (ipp & 1) i ^= direction_numbers_[(j - l) * dimensions_ + k];
                    ipp >>= 1;
                }

                direction_numbers_[j * dimensions_ + k] = i;
            }
        }  
    }
    double SobolGenerator::get_uniform_quasi(){
         // Generate next Sobol vector component
        long long n = current_index_;
        int j;
        for (j = 0; j < MAXBIT; j++) {
            if (!(n & 1)) break;
            n >>= 1;
        }

        if (j >= MAXBIT) {
            throw std::runtime_error("MAXBIT too small in sobol sequence");
        }

        for (int k = 0; k < dimensions_; k++) {
            current_int_state_[k] ^= direction_numbers_[j * dimensions_ + k];
        }

        current_index_++;

        // Return first component for single uniform number
        return current_int_state_[0] * normalization_factor_;
    }

    double SobolGenerator::get_normal(){
        // use the box-muller transformation to covert uniform to normal
        bool has_cached = false;
        double cached = 0.0;

        if (has_cached) {
            has_cached = false;
            return cached;
        }

        double u1 = get_uniform_quasi();
        double u2 = get_uniform_quasi();
        double r = std::sqrt(-2.0 * std::log(u1));
        double theta = 2.0 * M_PI * u2;

        cached = r * std::sin(theta);
        has_cached = true;
        return r * std::cos(theta); 
    }

    void SobolGenerator::fill_normal_vector(std::vector<double>& out_vector) {
        out_vector.resize(dimensions_);
        for (double& v : out_vector){
            v = get_normal();
        }
    }

    void SobolGenerator::reset() {
        current_index_ = 0;
        std::fill(current_int_state_.begin(), current_int_state_.end(), 0);
    }

}

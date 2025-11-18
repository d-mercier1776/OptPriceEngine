#include "sobol_generator.h"
#include <cmath>
#include <algorithm>
#include <stdexcept>
#include <string>

// max bits for precision 
#define MAXBIT 30 
// max support dimension based on the direction numbers available
#define MAXDIM 40

// Static Direction Number Data (Joe/Kuo based)
// Degree of the primitive polynomial (d) for dimensions 1 to 40.
static const int deg[MAXDIM] = {
    1, 2, 3, 3, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7
};

// The coefficients (A values) for the primitive polynomials for dimensions 1 to 40.
// This defines which prior terms in the recurrence are XORed.
static const unsigned int a[MAXDIM] = {
    0, 1, 1, 2, 1, 4, 2, 4, 8, 11, 2, 4, 8, 16, 17, 20, 26, 30, 31, 32, 2, 4, 8, 16, 32, 33, 40, 48, 56, 63, 64, 72, 80, 88, 96, 104, 112, 120, 127, 128
};

// Initial direction numbers (V values). We assume V_1 = 1 for all dimensions,
// this simplication when the full set of initial direction numbers is not provided.
static const unsigned int v_first_row[MAXDIM] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};

namespace utils{
    /**
     *  @brief Constructor: Initializes the Sobol generator using Joe/Kuo parameters.
    */
    SobalGenerator::SobalGenerator(int dimensions)
                    :dimensions_(dimensions),
                     current_index_(0),
                     current_int_state_(dimensions), 
                     direction_numbers_(dimensions * MAXBIT)
    {
        if(dimensions_ <=0 || dimensions > MAXDIM){
           throw std::out_of_range("Sobol Generator dimensions must be between 1 and MAXDIM (" + std::to_string(MAXDIM) + ").");
        }
        // 1. compute the normalization factor: 1.0 / 2^ MAXBIT
        normalization_factor_ = 1.0 / (1.0 * (1u< MAXBIT));
        
        // get the pointer to start of the direction numbers
        unsigned int* iv_ptr = direction_numbers_.data();

        // 2. compute Direction Numbers (joe/ku recurrence)
        // load and shift the first row of direction numbers (v_1)
        for(int k = 0; k< dimensions_;++k){
            // index j = 0, k = dimensions
            iv_ptr[0* dimensions_ + k] = v_first_row[k];

            // v_j is scaled by 2^(MAXBIT-j) for j = 1 and this is 2^(MAXBIT-1)
            iv_ptr[0 * dimensions_ + k] <<= (MAXBIT - 1);
        }
        // use the reurrence relation to calculate the rest (V2 to V mAXBIT)
        
    }
}
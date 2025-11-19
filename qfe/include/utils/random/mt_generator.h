#pragma once

#include "i_random_generator.h"
#include <random>
namespace utils{
    class MTGenerator : public IRandomGenerator{
        public: 
            // constructor: take a seed 
            MTGenerator(unsigned int seed = std::random_device{}());
            // implementation of the interface methods 
            double get_normal() override;
            void fill_normal_vector(std::vector<double>& out_vector) override;
            void reset() override;
        private:
            std::mt19937 mt_engine_;
            std::uniform_real_distribution<> uniform_dist_; // internal 
            std::normal_distribution<> normal_dist_; 
            unsigned int initial_seed_;
    };
}
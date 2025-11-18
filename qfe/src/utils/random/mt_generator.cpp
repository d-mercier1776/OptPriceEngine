#include "mt_generator.h"
namespace utils {

    MTGenerator::MTGenerator(unsigned int seed): 
                mt_engine_(seed), 
                uniform_dist_(0.0, 1.0),
                normal_dist_(0.0, 1.0), 
                initial_seed_(seed){}
    
    double MTGenerator::get_normal(){
        return normal_dist_(mt_engine_);
    }
    void MTGenerator::fill_normal_vector(std::vector<double>& out_vector){
        for(double &value: out_vector){
            value = get_normal();
        }
    }
    void MTGenerator::reset(){
        mt_engine_.seed(initial_seed_);
    }
}
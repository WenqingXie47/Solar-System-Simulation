#ifndef nbsimStableConditionGenerator_h
#define nbsimStableConditionGenerator_h
#include "nbsimInitialConditionGenerator.h"

namespace nbsim {

class StableConditionGenerator : public InitialConditionGenerator{

public:
    StableConditionGenerator
        (double mu_central = 39.4784, 
        double r_min=0.4, double r_max=40,
        double mu_min = 1e-6,double mu_max=1e-3);
    std::vector<MassiveParticle> generateInitialCondition(int size);

private:
    std::default_random_engine generator;
    double mu_central;
    std::uniform_real_distribution<double> distribution_r;
    std::uniform_real_distribution<double> distribution_theta;
    std::uniform_real_distribution<double> distribution_mu;
};



} // end namespace nbsim


#endif
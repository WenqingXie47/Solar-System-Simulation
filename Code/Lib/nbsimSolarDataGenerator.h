#ifndef nbsimSolarDataGenerator_h
#define nbsimSolarDataGenerator_h
#include "nbsimDataGenerator.h"

namespace nbsim {

class SolarDataGenerator : public DataGenerator{

public:
    SolarDataGenerator();
    std::vector<MassiveParticle> generateData(int size);

private:
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution_r;
    std::uniform_real_distribution<double> distribution_theta;
    std::uniform_real_distribution<double> distribution_mu;
};



} // end namespace nbsim


#endif
#ifndef nbsimDataGenerator_h
#define nbsimDataGenerator_h
#include <random>
#include <vector>
#include "nbsimMassiveParticle.h"


namespace nbsim{

class DataGenerator{
public:
    virtual std::vector<MassiveParticle> generateData(int size)=0;
private:
};


} // end namespace nbsim

#endif
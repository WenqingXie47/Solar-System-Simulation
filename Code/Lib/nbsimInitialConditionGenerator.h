#ifndef nbsimInitialConditionGenerator_h
#define nbsimInitialConditionGenerator_h
#include <random>
#include <vector>
#include "nbsimMassiveParticle.h"


namespace nbsim{

class InitialConditionGenerator{
public:
    virtual std::vector<MassiveParticle> generateInitialCondition(int size)=0;
private:
};


} // end namespace nbsim

#endif
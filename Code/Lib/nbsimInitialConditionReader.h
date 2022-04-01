#ifndef nbsimInitialConditionReader_h
#define nbsimInitialConditionReader_h
#include <vector>
#include "nbsimMassiveParticle.h"

namespace nbsim
{


class  InitialConditionReader{

public:
    template <typename S> 
    static MassiveParticle readMassiveParticle(const S& particleData){
        nbsim::MassiveParticle p{
            particleData.mu,
            particleData.position,
            particleData.velocity
        };
        p.setName(particleData.name);
        return p;
    }

    template <typename T>
    static std::vector<MassiveParticle> readInitialCondition(const T &data){
        std::vector<MassiveParticle> initialCondition{};
        for (const auto &elem : data){
            initialCondition.push_back(readMassiveParticle(elem));
        }
        return initialCondition;
    };

}; 

} // end namespace nbsim

#endif



#ifndef nbsimMassiveParticle_h
#define nbsimMassiveParticle_h

#include "nbsimParticle.h"
#include <set>

namespace nbsim {

class MassiveParticle : public Particle
{
public:
    MassiveParticle(double mu, const Eigen::Vector3d& position, const Eigen::Vector3d& velocity);
    double getMu() const;
    void addAttractor(const MassiveParticle& attractor);
    void removeAttractor(const MassiveParticle& attractor);
    void calculateAcceleration();

    void integrateTimestep(double timestep);

    // calculate energy
    double calculateKineticEnergy() const;
    double calculatePotentialEnergy() const;
    double calculateTotalEnergy() const;


private:
    double mu;  // mu = G*m,  G is gravitational constant and m is mass
    Eigen::Vector3d acceleration;
    std::set<const MassiveParticle*>  attractors;

    Eigen::Vector3d calculateAcceleration(const MassiveParticle& attractor);
};


} // end namespace nbsim
#endif
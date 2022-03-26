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
    void integrateTimestep(const double timestep);

private:
    double mu;  // mu = G*m,  G is gravitational constant and m is mass
    Eigen::Vector3d acceleration;
    std::set<const MassiveParticle*>  attractors;

    Eigen::Vector3d calculateAcceleration
        (double mu,const Eigen::Vector3d& relativePosition) const;
};


} // end namespace nbsim
#endif
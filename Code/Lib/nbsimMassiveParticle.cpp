#include "nbsimMassiveParticle.h"
#include <cmath>

namespace nbsim
{

MassiveParticle::MassiveParticle(double mu, const Eigen::Vector3d& position, const Eigen::Vector3d& velocity)
    :Particle{position,velocity}, mu{mu}, attractors{}
{}

double MassiveParticle::getMu() const
{
    return mu;
}

void MassiveParticle::addAttractor(const MassiveParticle* attractor)
{
    attractors.insert(attractor);
}

void MassiveParticle::removeAttractor(const MassiveParticle* attractor)
{
    attractors.erase(attractor);
}

void MassiveParticle::calculateAcceleration()
{
    // clear value from the last step
    acceleration = Eigen::Vector3d(0,0,0);
    for (auto attractor : attractors){
        double attractorMu = attractor->getMu();
        Eigen::Vector3d attractorPosition = attractor->getPosition();
        Eigen::Vector3d relativePosition = attractorPosition - (this->getPosition());
        acceleration += calculateAcceleration(attractorMu,relativePosition);
    }
}

Eigen::Vector3d MassiveParticle::calculateAcceleration
    (double mu,const Eigen::Vector3d& relativePosition) const
{
    double r_square = relativePosition.dot(relativePosition);
    Eigen::Vector3d r_normalized = relativePosition/sqrt(r_square);
    return -r_normalized*mu/r_square;
}

void MassiveParticle::integrateTimestep(const double timestep)
{
   Particle::integrateTimestep(acceleration,timestep);
}

} // end namespace nbsim
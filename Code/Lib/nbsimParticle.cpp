#include "nbsimParticle.h"

namespace nbsim
{

Particle::Particle(const Eigen::Vector3d& position, const Eigen::Vector3d& velocity)
    : x{position}, v{velocity}
{}

Particle::~Particle()
{}

Eigen::Vector3d Particle::getPosition() const
{
    return x;
}

Eigen::Vector3d Particle::getVelocity() const
{
    return v;
}

void Particle::integrateTimestep(const Eigen::Vector3d& acceleration, const double timestep)
{
    x += v*timestep;
    v += acceleration*timestep;
}   


} // end namespace nbsim

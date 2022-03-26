#include "nbsimParticle.h"

namespace nbsim
{

Particle::Particle(const Eigen::Vector3d& position, const Eigen::Vector3d& velocity)
    : position{position}, velocity{velocity}
{}

Particle::~Particle()
{}

Eigen::Vector3d Particle::getPosition() const
{
    return position;
}

Eigen::Vector3d Particle::getVelocity() const
{
    return velocity;
}

void Particle::integrateTimestep(const Eigen::Vector3d& acceleration, const double timestep)
{
    position += velocity*timestep;
    velocity += acceleration*timestep;
}   


} // end namespace nbsim

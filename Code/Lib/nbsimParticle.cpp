#include "nbsimParticle.h"
#include <iostream>

namespace nbsim
{

Particle::Particle(const Eigen::Vector3d& position, const Eigen::Vector3d& velocity)
    : position{position}, velocity{velocity}
{}

Particle::~Particle()
{}

bool Particle::operator==(const Particle& other) const
{
    return (this==&other);
}

bool Particle::operator!=(const Particle& other) const
{
    return !(*this==other);
}

Eigen::Vector3d Particle::getPosition() const
{
    return position;
}

Eigen::Vector3d Particle::getVelocity() const
{
    return velocity;
}

std::string Particle::getName() const
{
    return name;
}

void Particle::setName(std::string particleName)
{
    name = particleName;
}

void Particle::integrateTimestep(const Eigen::Vector3d& acceleration, const double timestep)
{
    position += velocity*timestep;
    velocity += acceleration*timestep;
}   

void Particle::printInfo() const
{
    std::cout<< "Name: " << name << "\t"
        << "position: (" << position.transpose() << ")\t"
        << "velocity: (" << velocity.transpose() << ")\n";
}


} // end namespace nbsim

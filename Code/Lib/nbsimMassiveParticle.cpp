#include "nbsimMassiveParticle.h"
#include "nbsimException.h"
#include <cmath>
#include <limits> 


namespace nbsim
{

MassiveParticle::MassiveParticle(double mu, const Eigen::Vector3d& position, const Eigen::Vector3d& velocity)
    :Particle{position,velocity}, mu{mu}, attractors{}
{
    if(mu<0){
        throw std::range_error("Invalid Mu value: mu cannot be negative.");
    }
}

double MassiveParticle::getMu() const
{
    return mu;
}

void MassiveParticle::addAttractor(const MassiveParticle& attractor)
{
    // One particle cannot attractor of itself 
    if(*this == attractor){
        return;
    }
    // avoid repeated attractor
    for(const auto& attractorPointer: attractors){
        if(attractor == *attractorPointer){
            return;
        }
    }
    attractors.insert(&attractor);
}

void MassiveParticle::removeAttractor(const MassiveParticle& attractor)
{
    attractors.erase(&attractor);
}

void MassiveParticle::calculateAcceleration()
{
    // clear value from the last step
    acceleration = Eigen::Vector3d(0,0,0);
    for (auto attractor : attractors){
        acceleration += calculateAcceleration(*attractor);
    }
}

Eigen::Vector3d MassiveParticle::calculateAcceleration(const MassiveParticle& attractor)
{
    Eigen::Vector3d relativePosition = attractor.getPosition() - (this->getPosition());
    double r_square = relativePosition.dot(relativePosition);
    // When two particles get close, they collide and scatter.
    // In our simulation, there are only gravity,
    // but no electromagnetism force so they will not collide.
    // They will rotate around each other faster when they get closer
    Eigen::Vector3d r_normalized = relativePosition/sqrt(r_square);  
    double mu = attractor.getMu();
    return r_normalized*mu/r_square;
}

void MassiveParticle::integrateTimestep(double timestep)
{
   Particle::integrateTimestep(acceleration,timestep);
}

} // end namespace nbsim
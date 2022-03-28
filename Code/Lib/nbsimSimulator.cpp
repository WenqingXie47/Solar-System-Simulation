#include "nbsimSimulator.h"
#include "nbsimException.h"
#include <iostream>
namespace nbsim{

Simulator::Simulator(const std::vector<MassiveParticle>& planetData, double timestep)
    :planets{planetData}
{
    setTimestep(timestep);
    // Add all other planets to list of attractors
    for (MassiveParticle& planet: planets){
        for (const MassiveParticle& attractor: planets){
            if(attractor!= planet){
                planet.addAttractor(attractor);
            }
        }
    }
}

Simulator::Simulator(std::vector<MassiveParticle>&& planetData, double timestep)
    :planets{planetData}
{
    setTimestep(timestep);
    // Add all other planets to list of attractors
    for (MassiveParticle& planet: planets){
        for (const MassiveParticle& attractor: planets){
            if(attractor!= planet){
                planet.addAttractor(attractor);
            }
        }
    }
}

Simulator::~Simulator(){}

double Simulator::getTimestep() const
{
    return timestep;
}

void Simulator::setTimestep(double simulationTimestep)
{
    if(simulationTimestep <= 0){
        throw std::range_error("Invalid timestep: timestep must be positive.");
    }
    timestep = simulationTimestep;
}

void Simulator::takeStep()
{
    for(MassiveParticle& planet : planets){
        planet.calculateAcceleration();
    }
    for(MassiveParticle& planet : planets){
        planet.integrateTimestep(timestep);
    }
}

void Simulator::simulate(int nSteps)
{
    for (int i=0; i<nSteps;i++){
        takeStep();
    }
}

void Simulator::printPlanets() const
{
    for (const auto& planet :planets){
        planet.printInfo();
    }
    std::cout<< std::endl;
}

} // end namespace nbsim
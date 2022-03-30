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


double Simulator::calculateKineticEnergy() const
{
    double kineticEnergy = 0;
    for(const MassiveParticle& planet: planets){
        kineticEnergy += planet.calculateKineticEnergy();
    }
    return kineticEnergy;
}

double Simulator::calculatePotentialEnergy() const
{
    double potentialEnergy = 0;
    for(const MassiveParticle& planet: planets){
        potentialEnergy += planet.calculatePotentialEnergy();
    }
    return potentialEnergy;
}
double Simulator::calculateTotalEnergy() const
{
    return calculateKineticEnergy()+ calculatePotentialEnergy();
}


void Simulator::printPlanets() const
{
    for (const auto& planet :planets){
        planet.printStatus();
    }
}

void Simulator::printEnergy() const
{
    double kineticEnergy = calculateKineticEnergy();
    double potentialEnergy = calculatePotentialEnergy();
    double totalEnergy = kineticEnergy+potentialEnergy;
    std::cout<< "Kinetic energy: " << kineticEnergy << "\t"
        << "Potential energy: " << potentialEnergy << "\t"
        << "Total energy: " << totalEnergy << "\n";
}

void Simulator::printStatus() const
{
    printPlanets();
    printEnergy();
    std::cout << std::endl;
}
} // end namespace nbsim
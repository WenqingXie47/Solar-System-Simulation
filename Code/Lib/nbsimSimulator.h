#ifndef nbsimSimulator_h
#define nbsimSimulator_h
#include "nbsimMassiveParticle.h"
#include <vector>
#include <string>


namespace nbsim{

class Simulator
{
public:
    // constructor and deconstuctor 
    Simulator(const std::vector<MassiveParticle>& planetData, double timestep);
    Simulator(std::vector<MassiveParticle>&& planetData, double timestep);
    ~Simulator();

    // getter and setter
    double getTimestep() const;
    void setTimestep(double simulationTimestep);

    // simulation
    void takeStep();
    void simulate(int nSteps);

    // calculate energy
    double calculateKineticEnergy() const;
    double calculatePotentialEnergy() const;
    double calculateTotalEnergy() const;

    // printing
    void printPlanets() const;
    void printEnergy() const;
    void printStatus() const;
private:
    std::vector<MassiveParticle> planets;
    double timestep;
};


} // end namespace nbsim

#endif
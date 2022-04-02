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
    void takeStep_openMP();
    void simulate(int nSteps);
    void simulate_openMP(int nSteps);

    // calculate energy
    double calculateKineticEnergy() const;
    double calculateKineticEnergy_openMP() const;
    double calculatePotentialEnergy() const;
    double calculatePotentialEnergy_openMP() const;
    double calculateTotalEnergy() const;
    double calculateTotalEnergy_openMP() const;

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
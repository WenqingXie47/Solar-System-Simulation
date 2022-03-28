#ifndef nbsimSimulator_h
#define nbsimSimulator_h
#include "nbsimMassiveParticle.h"
#include <vector>
#include <string>


namespace nbsim{

class Simulator
{
public:
    Simulator(const std::vector<MassiveParticle>& planetData, double timestep);
    Simulator(std::vector<MassiveParticle>&& planetData, double timestep);
    ~Simulator();
    double getTimestep() const;
    void setTimestep(double simulationTimestep);
    void takeStep();
    void simulate(int nSteps);
    void printPlanets() const;
private:
    std::vector<MassiveParticle> planets;
    double timestep;
};


} // end namespace nbsim

#endif
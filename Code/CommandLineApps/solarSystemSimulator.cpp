
#include "CLI11.hpp"
#include "nbsimSimulator.h"
#include "nbsimSolarSystemData.ipp"
#include <iostream>
#include <vector>

std::vector<nbsim::MassiveParticle> preparData();
void simulate(double timestep, int nSteps);

int main(int argc, char **argv) {
    CLI::App app;

    // time length for a single step
    double timestep =  0;
    // length of total simulation time
    double simulationTime = 0;
    // total number of steps
    int nSteps = 0;

    auto op_stepSize = app.add_option("-s,--stepSize", timestep, "Specify the time length for a single step");
    auto op_nSteps = app.add_option("-n,--nSteps", nSteps, "Specify the number of steps to simulate");
    auto op_time = app.add_option("-t,--time", simulationTime, "Specify the total length of time to simulate");

    op_stepSize->required();
    op_nSteps->excludes(op_time);

    if (argc < 2){
        std::cerr<< app.help() << std::endl;
        return 1;
    }
    CLI11_PARSE(app, argc, argv);

    if(simulationTime>0){
        nSteps = (int) (simulationTime/timestep);
        simulate(timestep, nSteps);
        return 0;
    }

    if(nSteps > 0){
        simulate(timestep,  nSteps);
        return 0;
    }

    std::cerr<< app.help() << std::endl;
    return 1;
}


std::vector<nbsim::MassiveParticle> preparData()
{
    std::vector<nbsim::MassiveParticle> data;
    for(const nbsim::Planet& planet : nbsim::solarSystemData){
        nbsim::MassiveParticle massivePlanet{
            planet.mu,
            planet.position,
            planet.velocity
        };
        massivePlanet.setName(planet.name);
        data.push_back(massivePlanet);
    }
    return data;
}

void simulate(double timestep, int nSteps)
{
    nbsim::Simulator simulator{preparData(),timestep};
    simulator.printPlanets();
    simulator.simulate(nSteps);
    simulator.printPlanets();
}


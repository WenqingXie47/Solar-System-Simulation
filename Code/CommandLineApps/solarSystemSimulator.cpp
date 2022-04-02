
#include "CLI11.hpp"
#include "nbsimSimulator.h"
#include "nbsimInitialConditionReader.h"
#include "nbsimSolarSystemData.ipp"
#include <iostream>
#include <vector>


void simulateSolarSystem(double timestep, int nSteps);

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

    if(timestep<=0 ){
        std::cerr << "The stepSize of simulation should be positive.\n"
        << app.help() << std::endl;
    }

    if(simulationTime>0){
        nSteps = (int) (simulationTime/timestep);
        simulateSolarSystem(timestep, nSteps);
        return 0;
    }

    if(nSteps > 0){
        simulateSolarSystem(timestep,  nSteps);
        return 0;
    }

    std::cerr<< "The nSteps or the simulationTime should be positive.\n"
    << app.help() << std::endl;
    return 1;
}



void simulateSolarSystem(double timestep, int nSteps)
{
    auto initialCondition = nbsim::InitialConditionReader::readInitialCondition(
        nbsim::solarSystemData
    );
    nbsim::Simulator simulator{initialCondition,timestep};
    std::cout<< "Initial condition:" << std::endl;
    simulator.printStatus();
    simulator.simulate(nSteps);
    std::cout<< "Final status:" << std::endl;
    simulator.printStatus();
}


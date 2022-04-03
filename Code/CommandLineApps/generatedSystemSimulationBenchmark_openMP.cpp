#include "nbsimSimulator.h"
#include "nbsimStableConditionGenerator.h"
#include "nbsimSolarSystemData.ipp"
#include <iostream>
#include <cmath>
#include <ctime>
#include <chrono>

int main()
{
    nbsim::StableConditionGenerator generator{};
    int size = 2000; // we want to generatr 2000 random particles
    auto initialCondition = generator.generateInitialCondition(size);

    double simulationTime = 4; // 4 year
    double timestep = 0.00274; // about 1 day
    int nSteps = (int) (simulationTime/timestep);

    nbsim::Simulator simulator{initialCondition,timestep};
    // calculate energy at the initial condition
    double kineticEnergy_begin = simulator.calculateKineticEnergy_openMP();
    double potentialEnergy_begin =simulator.calculatePotentialEnergy_openMP();
    double totalEnergy_begin = kineticEnergy_begin+ potentialEnergy_begin;
    // time the simulation
    std::clock_t c_start = std::clock();
    auto t_start = std::chrono::high_resolution_clock::now();
    simulator.simulate_openMP(nSteps);
    auto t_end = std::chrono::high_resolution_clock::now();
    std::clock_t c_end = std::clock();
    // calculate energy at the end state
    double kineticEnergy_end = simulator.calculateKineticEnergy_openMP();
    double potentialEnergy_end =simulator.calculatePotentialEnergy_openMP();
    double totalEnergy_end = kineticEnergy_end+potentialEnergy_end;


    double error_energy = abs((totalEnergy_end- totalEnergy_begin)/totalEnergy_begin);
    auto wall_clock_duration = std::chrono::duration<double, std::milli>(t_end-t_start).count();
    auto cpu_duration = 1000.0 * (c_end - c_start) / CLOCKS_PER_SEC;

    std::cout << "Timestep size: " << timestep << "\t"
            << "Total simulation time: " << simulationTime << "\n"
            << "Begin:\t" 
            << "Kinetic energy: " << kineticEnergy_begin << "\t"
            << "Potential energy: " << potentialEnergy_begin << "\t"
            << "Total energy: " << totalEnergy_begin << "\n"
            << "End:\t" 
            << "Kinetic energy: " << kineticEnergy_end << "\t"
            << "Potential energy: " << potentialEnergy_end << "\t"
            << "Total energy: " << totalEnergy_end << "\n"
            << "Relative error of total energy: " << error_energy << "\n"
            << "Wall clock time duration: " << wall_clock_duration <<  " ms" << "\n"
            << "CPU time duration: " << cpu_duration <<  " ms" << "\n" 
            << std::endl;
            
    return 0;
}
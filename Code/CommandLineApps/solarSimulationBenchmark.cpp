#include "nbsimSimulator.h"
#include "nbsimSolarSystemData.ipp"
#include <iostream>
#include <cmath>
#include <chrono>

std::vector<nbsim::MassiveParticle> preparData();

int main()
{
    auto data = preparData();
    double simulationTime = 100.0; // 100 year
    double timestep = 0.00274; // about 1 day


    // 8 differemnt timeStep are tried
    for (int i=0 ; i<8; i++){
        int nSteps = (int) (simulationTime/timestep);

        nbsim::Simulator simulator{data,timestep};
        double energy_begin = simulator.calculateTotalEnergy();
        auto t_start = std::chrono::high_resolution_clock::now();
        simulator.simulate(nSteps);
        auto t_end = std::chrono::high_resolution_clock::now();
        double energy_end = simulator.calculateTotalEnergy();

        double error_energy = abs((energy_end- energy_begin)/energy_begin);
        auto duration = std::chrono::duration<double, std::milli>(t_end-t_start).count();

        std::cout << "Timestep sizes: " << timestep << "\t"
                << "Relative error of energy: " << error_energy << "\t"
                << "Time duration: " << duration <<  " ms" << std::endl;

        timestep/=2;
    }
    return 0;
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
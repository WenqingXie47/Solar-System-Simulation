#include "catch.hpp"
#include "nbsimCatchMain.h"
#include "nbsimSimulator.h"
#include "nbsimSolarSystemData.ipp"

std::vector<nbsim::MassiveParticle> preparData();

TEST_CASE( "Initialize", "[Initialize]" ) {
    nbsim::Simulator simulator{preparData(),0.0001};
    simulator.printPlanets();
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
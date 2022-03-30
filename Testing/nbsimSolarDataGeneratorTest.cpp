#include "catch.hpp"
#include "nbsimCatchMain.h"
#include "nbsimSolarDataGenerator.h"


void printVector(std::vector<nbsim::MassiveParticle> vec)
{
    for (auto particle : vec){
        particle.printStatus();
    }
}

TEST_CASE( "Generation", "[Generation]" ) {
    nbsim::SolarDataGenerator generator{};
    auto v = generator.generateData(20);
    printVector(v);
}

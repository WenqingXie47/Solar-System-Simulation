#include "catch.hpp"
#include "nbsimCatchMain.h"
#include "nbsimStableConditionGenerator.h"


void printVector(std::vector<nbsim::MassiveParticle> vec)
{
    for (auto particle : vec){
        particle.printStatus();
    }
}

TEST_CASE( "Generation", "[Generation]" ) {
    nbsim::StableConditionGenerator generator{};
    auto planets= generator.generateInitialCondition(10);

    
}

#include "catch.hpp"
#include "nbsimCatchMain.h"
#include "nbsimStableConditionGenerator.h"
#include "nbsimSimulator.h"



TEST_CASE( "Generation", "[Generation]" ) {
    nbsim::StableConditionGenerator generator{};
    auto stableCondition= generator.generateInitialCondition(10);
    for (auto particle : stableCondition){
        particle.printStatus();
    }


    double timestep = 0.000274;
    nbsim::Simulator simulator{stableCondition, timestep};
    double initialEnergy = simulator.calculateTotalEnergy();
    int steps = 3650;
    simulator.simulate(steps);
    double finalEnergy = simulator.calculateTotalEnergy();

    const double precision = 0.01;
    REQUIRE(finalEnergy ==  Approx(initialEnergy).epsilon(precision));
}

#include "catch.hpp"
#include "nbsimCatchMain.h"
#include "nbsimSimulator.h"
#include "nbsimSolarSystemData.ipp"
#include "nbsimInitialConditionReader.h"



TEST_CASE( "Two body", "[Two body]" ) {
    double mu = 1;
    Eigen::Vector3d x1(1,0,0);
    Eigen::Vector3d v1(0,0.5,0);
    Eigen::Vector3d x2(-1,0,0);
    Eigen::Vector3d v2(0,-0.5,0);
    // not real earch and moon
    nbsim::MassiveParticle earth{mu,x1,v1};
    nbsim::MassiveParticle moon{mu,x2,v2};

    std::vector<nbsim::MassiveParticle> initialCondition;
    initialCondition.push_back(earth);
    initialCondition.push_back(moon);
    
    double timestep = 0.000274;
    nbsim::Simulator simulator{initialCondition,timestep};
    double initialEnergy = simulator.calculateTotalEnergy();
    int steps = 3650;
    simulator.simulate(steps);
    double finalEnergy = simulator.calculateTotalEnergy();

    const double precision = 0.01;
    REQUIRE(finalEnergy ==  Approx(initialEnergy ).epsilon(precision));
}


TEST_CASE( "Solar System", "[Solar System]" ) {
    double timestep = 0.000274;
    auto initialCondition = nbsim::InitialConditionReader::readInitialCondition(
        nbsim::solarSystemData
    );
    nbsim::Simulator simulator{initialCondition,timestep};

    double initialEnergy = simulator.calculateTotalEnergy();
    int steps = 3650;
    simulator.simulate(steps);
    double finalEnergy = simulator.calculateTotalEnergy();

    const double precision = 0.01;
    REQUIRE(finalEnergy ==  Approx(initialEnergy).epsilon(precision));
}


 
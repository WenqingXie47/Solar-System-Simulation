#include "catch.hpp"
#include "nbsimCatchMain.h"
#include "nbsimInitialConditionReader.h"
#include "nbsimSimulator.h"
#include "nbsimSolarSystemData.ipp"

TEST_CASE( "Read data", "[Read data]" ) {
    auto initialCondition = nbsim::InitialConditionReader::readInitialCondition(
        nbsim::solarSystemData
    );
    double timestep = 0.00274;
    nbsim::Simulator simulator(initialCondition,timestep);
    simulator.printStatus();
}


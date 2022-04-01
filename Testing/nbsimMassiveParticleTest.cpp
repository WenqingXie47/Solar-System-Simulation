#include "catch.hpp"
#include "nbsimCatchMain.h"
#include "nbsimMassiveParticle.h"
#include <cmath>




TEST_CASE( "No acceleration", "[No acceleration]" ) {
    double mu = 1;
    Eigen::Vector3d position(0,0,0);
    Eigen::Vector3d velocity(1,0,0);

    const double timestep = 0.001;
    const double precision = 0.01;
    nbsim::MassiveParticle earth{mu,position,velocity};
    for (int n=0; n<100000; n++){
        double time = timestep*n;
        REQUIRE( earth.getPosition().isApprox(position+velocity*time,precision));
        REQUIRE( earth.getVelocity().isApprox(velocity,precision));
        earth.calculateAcceleration();
        earth.integrateTimestep(timestep);
    }  
}

TEST_CASE( "Two body", "[Two body]" ) {
    double mu = 1;
    Eigen::Vector3d x1(1,0,0);
    Eigen::Vector3d v1(0,0.5,0);
    Eigen::Vector3d x2(-1,0,0);
    Eigen::Vector3d v2(0,-0.5,0);

    // not real earch and moon
    nbsim::MassiveParticle earth{mu,x1,v1};
    nbsim::MassiveParticle moon{mu,x2,v2};
    earth.addAttractor(moon);
    moon.addAttractor(earth);

    const double timestep = 0.0001;
    int nSteps = (int) (4*M_PI/timestep);
    const double precision = 0.1;
    for (int n=0; n<nSteps; n++){
        double time = timestep*n;

        Eigen::Vector3d relativePosition = moon.getPosition() - earth.getPosition();
        double distance = sqrt(relativePosition.dot(relativePosition));
        REQUIRE( distance == Approx(2).epsilon(precision));

        earth.calculateAcceleration();
        moon.calculateAcceleration();

        earth.integrateTimestep(timestep);
        moon.integrateTimestep(timestep);
    }  
}


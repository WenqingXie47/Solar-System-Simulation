#include "catch.hpp"
#include "nbsimCatchMain.h"
#include "nbsimParticle.h"
#include <cmath>


TEST_CASE( "No acceleration", "[No acceleration]" ) {
  Eigen::Vector3d position(0,0,0);
  Eigen::Vector3d velocity(1,0,0);
  Eigen::Vector3d acceleration(0,0,0);
  // the time step should be small enough
  const double timestep = 0.001;
  double precision = 0.01;
  nbsim::Particle electron{position,velocity};
  for (int n=0; n<100000; n++){
    double time = timestep*n;
    REQUIRE( electron.getPosition().isApprox(position+velocity*time,precision));
    REQUIRE( electron.getVelocity().isApprox(velocity,precision));
    electron.integrateTimestep(acceleration,timestep);
  }  
}

TEST_CASE( "Constant acceleration", "[Constant acceleration]" ) {
  Eigen::Vector3d position(0,0,0);
  Eigen::Vector3d velocity(0,0,1);
  Eigen::Vector3d acceleration(1,0,0);
  nbsim::Particle electron{position,velocity};
  const double timestep = 0.001;
  const int nSteps = 100000;
  for (int n=0; n<nSteps; n++){
    electron.integrateTimestep(acceleration,timestep);
  } 
  double time = timestep*nSteps;
  double precision = 0.01;
  REQUIRE( electron.getPosition().isApprox(position+velocity*time+acceleration*time*time/2,precision));
  REQUIRE( electron.getVelocity().isApprox(velocity+acceleration*time,precision));
}


TEST_CASE( "Fictitious centripetal acceleration", "[Fictitious centripetal acceleration]" ) {
  Eigen::Vector3d position(1,0,0);
  Eigen::Vector3d velocity(0,1,0);
  nbsim::Particle electron{position,velocity};

  double time = 2*M_PI;
  const double timestep = 0.001;
  int nSteps = (int) (time/timestep);
  for (int n=0; n<nSteps; n++){
    Eigen::Vector3d acceleration = -electron.getPosition();
    electron.integrateTimestep(acceleration,timestep);
  } 

  double precision = 0.01;
  REQUIRE( electron.getPosition().isApprox(position,precision));
  REQUIRE( electron.getVelocity().isApprox(velocity,precision));
}
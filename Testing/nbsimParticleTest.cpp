#include "catch.hpp"
#include "nbsimCatchMain.h"
#include "nbsimParticle.h"


TEST_CASE( "No acceleration", "[No acceleration]" ) {
  Eigen::Vector3d position(0,0,0);
  Eigen::Vector3d velocity(1,0,0);
  Eigen::Vector3d acceleration(0,0,0);
  double timestep = 1.0;
  nbsim::Particle electron{position,velocity};
  for (int n=0; n<100; n++){
    double time = timestep*n;
    REQUIRE( electron.getPosition().isApprox(position+velocity*time));
    REQUIRE( electron.getVelocity().isApprox(velocity));
    electron.integrateTimestep(acceleration,timestep);
  }  
}

// TEST_CASE( "Constant acceleration", "[No acceleration]" ) {
//   Eigen::Vector3d position(0,0,0);
//   Eigen::Vector3d velocity(0,0,0);
//   Eigen::Vector3d acceleration(1,0,0);
//   double timestep = 1.0;
//   nbsim::Particle electron{position,velocity};
//   for (int n=0; n<100; n++){
//     electron.integrateTimestep(acceleration,timestep);
//     double time = timestep*n;
//     REQUIRE( electron.getPosition().isApprox(position+velocity*time));
//     REQUIRE( electron.getVelocity().isApprox(velocity));
//   }  
// }

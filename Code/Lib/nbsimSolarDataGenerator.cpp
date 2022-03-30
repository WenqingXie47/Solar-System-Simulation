#include "nbsimSolarDataGenerator.h"
#include <chrono>
#include <cmath>


namespace nbsim{

SolarDataGenerator::SolarDataGenerator()
    :  distribution_r{0.4,40}, 
        distribution_theta{0, 2*M_PI},
        distribution_mu{0,0.01},
        generator(std::chrono::system_clock::now().time_since_epoch().count())
{}


std::vector<MassiveParticle> SolarDataGenerator::generateData(int size)
{
    std::vector<MassiveParticle> particleVector{};
    double mu_sun = 39.4784;
    Eigen::Vector3d zero_vec (0.0,0.0,0.0);
    MassiveParticle sun {mu_sun,zero_vec,zero_vec};

    // the central sun is the first massive particle
    particleVector.push_back(sun);

    for (int i=1; i<size; i++){
        double mu = distribution_mu(generator);
        double r = distribution_r(generator);
        double theta = distribution_theta(generator);
        Eigen::Vector3d position{r*sin(theta), r*cos(theta), 0};
        Eigen::Vector3d velocity{-mu_sun*cos(theta)/sqrt(r),
                                mu_sun*sin(theta)/sqrt(r),
                                0};
        particleVector.push_back(MassiveParticle{mu,position,velocity});
    }
    return particleVector;
}

} // end namespace nbsim
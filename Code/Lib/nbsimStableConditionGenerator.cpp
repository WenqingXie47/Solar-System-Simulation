#include "nbsimStableConditionGenerator.h"
#include <chrono>
#include <cmath>


namespace nbsim{

StableConditionGenerator::StableConditionGenerator
    (double mu_central, double r_min, double r_max,double mu_min,double mu_max)
    :   mu_central{mu_central},
        distribution_r{r_min,r_max}, 
        distribution_theta{0, 2*M_PI},
        distribution_mu{mu_min,mu_max},
        generator{}
        //generator(std::chrono::system_clock::now().time_since_epoch().count())

{}




std::vector<MassiveParticle> StableConditionGenerator::generateInitialCondition(int size)
{
    std::vector<MassiveParticle> particleVector{};
    Eigen::Vector3d zero_vec (0.0,0.0,0.0);
    // central body like the sun is the first particle
    MassiveParticle central_body {mu_central,zero_vec,zero_vec};
    particleVector.push_back(central_body);

    for (int i=1; i<size; i++){
        double mu = distribution_mu(generator);
        double r = distribution_r(generator);
        double theta = distribution_theta(generator);
        Eigen::Vector3d position{r*sin(theta), r*cos(theta), 0};
        Eigen::Vector3d velocity{-mu_central*cos(theta)/sqrt(r),
                                mu_central*sin(theta)/sqrt(r),
                                0};
        particleVector.push_back(MassiveParticle{mu,position,velocity});
    }
    return particleVector;
}

} // end namespace nbsim
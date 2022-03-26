#ifndef nbsimParticle_h
#define nbsimParticle_h
#include <Eigen/Dense>

namespace nbsim {

class Particle
{
public:
    // constructor and deconstructor 
    Particle(const Eigen::Vector3d& position, const Eigen::Vector3d& velocity);
    virtual ~Particle();

    // getter and setter 
    Eigen::Vector3d getPosition() const;
    Eigen::Vector3d getVelocity() const;

    void integrateTimestep(const Eigen::Vector3d& acceleration, const double timestep); 
private:
    Eigen::Vector3d position;
    Eigen::Vector3d velocity;
};

} // end namespace nbsim



#endif
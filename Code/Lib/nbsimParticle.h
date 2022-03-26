#ifndef nbsimMyFunctions_h
#define nbsimMyFunctions_h
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
    Eigen::Vector3d x;
    Eigen::Vector3d v;
};

} // end namespace nbsim



#endif
#ifndef nbsimParticle_h
#define nbsimParticle_h
#include <Eigen/Dense>
#include <string>

namespace nbsim {

class Particle
{
public:
    // constructor and deconstructor 
    Particle(const Eigen::Vector3d& position, const Eigen::Vector3d& velocity);
    virtual ~Particle();

    bool operator==(const Particle& other) const;
    bool operator!=(const Particle& other) const;

    // getter and setter 
    Eigen::Vector3d getPosition() const;
    Eigen::Vector3d getVelocity() const;
    std::string getName() const;
    void setName(std::string particleName);

    void integrateTimestep(const Eigen::Vector3d& acceleration, const double timestep); 
    void printInfo() const;
private:
    Eigen::Vector3d position;
    Eigen::Vector3d velocity;
    // default name
    std::string name = "unknown particle"; 
};

} // end namespace nbsim



#endif
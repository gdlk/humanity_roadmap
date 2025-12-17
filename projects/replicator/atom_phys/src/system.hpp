#pragma once

#include <vector>
#include <memory>
#include <span>

namespace atomphys {

struct Vec3 {
    double x, y, z;
    
    Vec3 operator+(const Vec3& other) const { return {x + other.x, y + other.y, z + other.z}; }
    Vec3 operator-(const Vec3& other) const { return {x - other.x, y - other.y, z - other.z}; }
    Vec3 operator*(double scalar) const { return {x * scalar, y * scalar, z * scalar}; }
};

class Integrator;

class System {
public:
    System();
    ~System();

    void addAtom(int type, double mass, double charge, Vec3 position);
    void setBox(Vec3 dimensions);
    void setIntegrator(std::shared_ptr<Integrator> integrator);
    
    void step(double dt);
    
    // Data Access (SoA)
    std::span<Vec3> getPositions() { return positions_; }
    std::span<Vec3> getVelocities() { return velocities_; }
    std::span<Vec3> getForces() { return forces_; }
    std::span<double> getMasses() { return masses_; }
    size_t getNumAtoms() const { return positions_.size(); }

    // Friend classes for internal access
    friend class Integrator;

private:
    // Structure of Arrays (SoA) for better cache locality
    std::vector<Vec3> positions_;
    std::vector<Vec3> velocities_;
    std::vector<Vec3> forces_;
    std::vector<double> masses_;
    std::vector<double> charges_;
    std::vector<int> types_;

    Vec3 box_;
    std::shared_ptr<Integrator> integrator_;
};

} // namespace atomphys
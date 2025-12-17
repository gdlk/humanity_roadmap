#include "integrator.hpp"

namespace atomphys {

void VelocityVerlet::integrate(System& system, double dt) {
    auto positions = system.getPositions();
    auto velocities = system.getVelocities();
    auto forces = system.getForces();
    auto masses = system.getMasses();
    size_t n = system.getNumAtoms();

    // First half-step for velocity and full step for position
    for (size_t i = 0; i < n; ++i) {
        double inv_mass = 1.0 / masses[i];
        Vec3 acceleration = forces[i] * inv_mass;
        
        velocities[i] = velocities[i] + acceleration * (0.5 * dt);
        positions[i] = positions[i] + velocities[i] * dt;
    }

    // Force calculation would happen here (currently placeholder)
    // In a real simulation, we would clear forces and re-calculate them based on new positions
    // system.computeForces(); 

    // Second half-step for velocity
    for (size_t i = 0; i < n; ++i) {
        double inv_mass = 1.0 / masses[i];
        Vec3 acceleration = forces[i] * inv_mass; // Using new forces
        
        velocities[i] = velocities[i] + acceleration * (0.5 * dt);
    }
}

} // namespace atomphys
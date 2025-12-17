#include "system.hpp"
#include "integrator.hpp"
#include <stdexcept>

namespace atomphys {

System::System() : box_{0, 0, 0} {}

System::~System() = default;

void System::addAtom(int type, double mass, double charge, Vec3 position) {
    types_.push_back(type);
    masses_.push_back(mass);
    charges_.push_back(charge);
    positions_.push_back(position);
    
    // Initialize velocity and force with zero
    velocities_.push_back({0, 0, 0});
    forces_.push_back({0, 0, 0});
}

void System::setBox(Vec3 dimensions) {
    box_ = dimensions;
}

void System::setIntegrator(std::shared_ptr<Integrator> integrator) {
    integrator_ = integrator;
}

void System::step(double dt) {
    if (!integrator_) {
        throw std::runtime_error("Integrator not set");
    }
    integrator_->integrate(*this, dt);
}

} // namespace atomphys
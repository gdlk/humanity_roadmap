#pragma once

#include "system.hpp"

namespace atomphys {

class Integrator {
public:
    virtual ~Integrator() = default;
    virtual void integrate(System& system, double dt) = 0;
};

class VelocityVerlet : public Integrator {
public:
    void integrate(System& system, double dt) override;
};

} // namespace atomphys
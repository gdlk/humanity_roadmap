#include <gtest/gtest.h>
#include "../src/system.hpp"
#include "../src/integrator.hpp"

using namespace atomphys;

TEST(SystemTest, AddAtom) {
    System sys;
    sys.addAtom(1, 12.0, 0.0, {0, 0, 0});
    
    EXPECT_EQ(sys.getNumAtoms(), 1);
    EXPECT_EQ(sys.getPositions()[0].x, 0.0);
    EXPECT_EQ(sys.getMasses()[0], 12.0);
}

TEST(IntegratorTest, ConstantVelocity) {
    System sys;
    sys.addAtom(1, 1.0, 0.0, {0, 0, 0});
    
    // Manually set velocity
    sys.getVelocities()[0] = {1.0, 0.0, 0.0};
    
    auto integrator = std::make_shared<VelocityVerlet>();
    sys.setIntegrator(integrator);
    
    // Step 1 second
    sys.step(1.0);
    
    // Position should be {1, 0, 0}
    EXPECT_DOUBLE_EQ(sys.getPositions()[0].x, 1.0);
    EXPECT_DOUBLE_EQ(sys.getPositions()[0].y, 0.0);
}

TEST(IntegratorTest, ConstantAcceleration) {
    System sys;
    sys.addAtom(1, 2.0, 0.0, {0, 0, 0}); // Mass = 2.0
    
    // Manually set force
    sys.getForces()[0] = {2.0, 0.0, 0.0}; // F = 2.0 -> a = F/m = 1.0
    
    auto integrator = std::make_shared<VelocityVerlet>();
    sys.setIntegrator(integrator);
    
    // Step 1 second
    // x = x0 + v0*t + 0.5*a*t^2 = 0 + 0 + 0.5*1*1 = 0.5
    // v = v0 + a*t = 0 + 1*1 = 1.0
    sys.step(1.0);
    
    EXPECT_DOUBLE_EQ(sys.getPositions()[0].x, 0.5);
    EXPECT_DOUBLE_EQ(sys.getVelocities()[0].x, 1.0);
}
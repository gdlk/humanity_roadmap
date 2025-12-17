add_library(atomphys_lib
    system.cpp
    integrator.cpp
)

target_include_directories(atomphys_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
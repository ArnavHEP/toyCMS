cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(Simulation)

find_package(Geant4 REQUIRED ui_all vis_all)

find_package(ROOT REQUIRED)
include(${ROOT_USE_FILE})

#find_package(PkgConfig REQUIRED)
#pkg_check_modules(HEPMC REQUIRED hepmc2)

include(${Geant4_USE_FILE})

file(GLOB sources ${PROJECT_SOURCE_DIR}/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/*.hh)

add_executable(sim sim.cc ${sources} ${headers})

target_link_libraries(sim ${Geant4_LIBRARIES})
target_link_libraries(sim ${ROOT_LIBRARIES})
target_link_libraries(sim HepMC)

target_include_directories(sim PRIVATE ${HEPMC_INCLUDE_DIRS})

add_custom_target(Simulation DEPENDS sim)

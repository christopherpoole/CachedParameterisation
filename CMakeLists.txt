####################################################
# CachedParameterisation 
#
# File:      CMakeLists.txt
#
# Author:    Christopher M Poole,
# Email:     mail@christopherpoole.net
#
# Date:      14th May, 2013
####################################################

cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(CACHEDPARAMETERISATION)

# GEANT4 core
find_package(Geant4 REQUIRED ui_all vis_all)
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

# G4VoxelData
find_package(G4VoxelData)
include_directories(/usr/local/include/cpp)

# User code
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh ${PROJECT_SOURCE_DIR}/../../include)

add_executable(CachedParam CachedParam.cc ${sources} ${headers})

target_link_libraries(CachedParam ${Geant4_LIBRARIES})
target_link_libraries(CachedParam ${G4VOXELDATA_HDF5_LIBRARIES})
target_link_libraries(CachedParam spatialindex)


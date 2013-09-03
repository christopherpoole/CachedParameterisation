# High fidelity parameterised geometry in GEANT4 described by data
GEANT4 provides a number of techniques for representing replica or similar repeating geometryCachedParameterisation aims to provide functionality for loading geometry described by data, where the memory requirement for the parameterisation itself as well as the data is larger than the available system memory.

# Patching GEANT4
This code requires a slight modification to `G4PVReplica`. We need to allow initialisation with zero replicas, and we add a `G4PVReplica::SetNoReplicas` method with we update based on the position of the current step. Replace the files in `patches` with the corresponding files in `geant4.9.6/source/geometry/volumes/` and recompile GEANT4.

# Dependencies
A number of dependencies are required for reading/writing data on disk as well as constructing the R* trees, and caching objects in memory:
    * [libspatialindex](https://github.com/libspatialindex/libspatialindex.git)
    *[LRUCache](https://patricaudley.com/code/project/lrucache)

# Compilation
    mkdir build/
    cd build/
    cmake ..
    make -j4
    cd ..

# Usage
See `macros/config.mac` for configuration options.

    ./build/CachedParam macros/vis.mac


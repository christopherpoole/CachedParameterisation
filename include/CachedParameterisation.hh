//////////////////////////////////////////////////////////////////////////
// CachedParameterisation
// ======================
// High fidelity parameterised geometry in GEANT4 described by data
//
// Author:  Christopher M Poole <mail@christopherpoole.net>
// Source:  http://github.com/christopherpoole/CachedParameterisation
//
// License & Copyright
// ===================
// 
// Copyright 2013 Christopher M Poole <mail@christopherpoole.net>
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//////////////////////////////////////////////////////////////////////////


#ifndef CACHEDPARAMETERISATOIN_H
#define CACHEDPARAMETERISATOIN_H


// GEANT4 //
#include "G4VPVParameterisation.hh"
#include "G4VPhysicalVolume.hh"

#include "globals.hh"
#include "Randomize.hh"

// G4VoxelData //
#include "G4VoxelData.hh"
#include "G4VoxelArray.hh"
#include "HDF5MappedIO.hh"

// SpatialIndex //
#include "spatialindex/SpatialIndex.h"


class CachedParameterisation : public G4VPVParameterisation{
  public:
    CachedParameterisation(G4String filename);
    ~CachedParameterisation();

  public:
    G4int GetSize();
    
    using G4VPVParameterisation::ComputeTransformation;
    void ComputeTransformation (const G4int copy_number,
            G4VPhysicalVolume* physical_volume) const;
 
    using G4VPVParameterisation::ComputeDimensions;

    using G4VPVParameterisation::ComputeMaterial;
    G4Material* ComputeMaterial(G4VPhysicalVolume *physical_volume,
            const G4int copy_number, const G4VTouchable *parent_touchable);
  
  private:
    G4int size;

    G4bool do_transform;
    G4bool do_dimensions;

    // Cached data files stored by copy number // 
    HDF5MappedIO<int>* transform;

    // SpatialIndex R* Tree //
    SpatialIndex::IStorageManager* rstar_file;
    SpatialIndex::StorageManager::IBuffer* rstar_buffer;
    SpatialIndex::ISpatialIndex* rstar_tree;
};

#endif // CACHEDPARAMETERISATOIN_H

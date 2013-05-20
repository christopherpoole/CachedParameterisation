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


// USER//
#include "CachedParameterisation.hh"
#include "DataStream.hh"


CachedParameterisation::CachedParameterisation(G4String filename)
{
    //this->size = transform->GetShape()[0];

    this->do_transform = true;
    this->do_dimensions = false;

    // Compute R* Tree
    rstar_file = SpatialIndex::StorageManager::createNewDiskStorageManager(
            filename, 4096);
    rstar_buffer = SpatialIndex::StorageManager::createNewRandomEvictionsBuffer(
            *rstar_file, 10, false);

    SpatialIndex::id_type indexIdentifier;
    double fill_factor = 0.7;
    int capacity = 100;
    int ndims = 3;

    rstar_tree = SpatialIndex::RTree::createNewRTree(
            *rstar_buffer, fill_factor, capacity, capacity, ndims, 
            SpatialIndex::RTree::RV_RSTAR, indexIdentifier);

    // for each replica
    // rstar_tree->insertData(uint32_t len, const byte* pData,
    //                        const IShape& shape, id_type shapeIdentifier);
    // where shape = SpatialIndex::Region(point_low, point_high, ndim=3)
    // point_low = [xmin, ymin, zmin], point_high = [xmax, ymax, zmax]
    // len and pData can be 0 for null pointer, could store replica metadata
}

CachedParameterisation::~CachedParameterisation()
{
}

G4int CachedParameterisation::GetSize()
{
    return this->size;
}

void CachedParameterisation::ComputeTransformation(const G4int copy_number,
        G4VPhysicalVolume* physical_volume) const
{
    G4int x = G4UniformRand()*2000;
    G4int y = G4UniformRand()*2000;
    G4int z = G4UniformRand()*2000;

    G4ThreeVector origin = G4ThreeVector(x, y, z);
    physical_volume->SetTranslation(origin);
}

G4Material* CachedParameterisation::ComputeMaterial(G4VPhysicalVolume *physical_volume,
            const G4int copy_number, const G4VTouchable *parent_touchable) {
}; 


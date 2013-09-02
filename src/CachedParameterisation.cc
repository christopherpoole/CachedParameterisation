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


CachedParameterisation::CachedParameterisation(G4String filename, G4String dataset)
{
    this->do_transform = true;
    this->do_dimensions = false;

    // Initialise LRU cache
    voxel_cache = new LRUCache<int, int>(10);

    // Initialise access to data on disk
    stream = new DataStream(filename, dataset);
    this->size = stream->size();

    BuildRTree(); 
}

CachedParameterisation::~CachedParameterisation()
{
}


void CachedParameterisation::ComputeTransformation(const G4int copy_number,
        G4VPhysicalVolume* physical_volume) const
{
    G4double x = this->x[copy_number];
    G4double y = this->y[copy_number];
    G4double z = this->z[copy_number];
    
    G4ThreeVector origin = G4ThreeVector(x, y, z);
    physical_volume->SetTranslation(origin);

    G4cout << origin << G4endl;
}

G4Material* CachedParameterisation::ComputeMaterial(G4VPhysicalVolume *physical_volume,
            const G4int copy_number, const G4VTouchable *parent_touchable) {
}; 

void CachedParameterisation::ComputeNeighbors(G4ThreeVector position, G4int number) {
    double p[3];
    p[0] = position.x();
    p[1] = position.y(); 
    p[2] = position.z();
    SpatialIndex::Point point = SpatialIndex::Point(p, 3);

    Visitor visitor;
    rstar_tree->nearestNeighborQuery(number, point, visitor);

    this->x = visitor.x;
    this->y = visitor.y;
    this->z = visitor.z;

    this->size = x.size();
};


void CachedParameterisation::BuildRTree() {
    // Compute R* Tree
    std::string name = "tree";
    rstar_file = SpatialIndex::StorageManager::createNewDiskStorageManager(
            name, 4096);
    rstar_buffer = SpatialIndex::StorageManager::createNewRandomEvictionsBuffer(
            *rstar_file, 10, false);

    SpatialIndex::id_type indexIdentifier;
    double fill_factor = 0.7;
    int index_capacity = 100;
    int leaf_capacity = 10;
    double utilisation = 0.4;
    int ndims = 3;

    rstar_tree = SpatialIndex::RTree::createAndBulkLoadNewRTree(
            SpatialIndex::RTree::BLM_STR, *stream, *rstar_file, utilisation,
            index_capacity, leaf_capacity, ndims,
            SpatialIndex::RTree::RV_RSTAR, indexIdentifier);
    
    std::cerr << *rstar_tree;
    std::cerr << "Buffer hits: " << rstar_buffer->getHits() << std::endl;
    std::cerr << "Index ID: " << indexIdentifier << std::endl;
};

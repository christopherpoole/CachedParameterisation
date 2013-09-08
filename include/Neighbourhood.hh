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


#ifndef Neighbourhood_h
#define Neighbourhood_h 1

// GEANT4 //
#include "globals.hh"

// USER //
#include "Helpers.hh"
#include "DataStream.hh"

// SpatialIndex //
#include "spatialindex/SpatialIndex.h"


class Neighbourhood
{
  public:
    Neighbourhood(G4String filename, G4String dataset) {
        // Initialise access to data on disk
        stream = new DataStream(filename, dataset);
        this->size = stream->size();

        BuildTree();
    };

    ~Neighbourhood() {
    };

  public:
    void BuildTree() {
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

    bool OutsideOfCurrentRegion(G4ThreeVector position) {
        SpatialIndex::Point point = Helpers::G4ThreeVectorToPoint(position);
        // If we are still in the current region, don't load another one.
        if (this->visitor.region.containsPoint(point)) {
                return false;
        }
        return true;
    };

    Visitor ComputeNeighbours(G4ThreeVector position, G4int number) {
        SpatialIndex::Point point = Helpers::G4ThreeVectorToPoint(position);
        
        Visitor visitor;
        rstar_tree->nearestNeighborQuery(number, point, visitor);
        
        // Operate on comparisons between the current and previous
        // visitor region here...

        this->visitor = visitor;
        return this->visitor;
    };

    unsigned int GetSize() {
        return this->size;
    }
  
  private:
    // SpatialIndex R* Tree //
    SpatialIndex::IStorageManager* rstar_file;
    SpatialIndex::StorageManager::IBuffer* rstar_buffer;
    SpatialIndex::ISpatialIndex* rstar_tree;
    Visitor visitor;

    // Data on disk
    DataStream* stream;

    unsigned int size;
};

#endif


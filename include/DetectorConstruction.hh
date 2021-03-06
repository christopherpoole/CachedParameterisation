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


#ifndef DetectorConstruction_H
#define DetectorConstruction_H

#include <vector>
#include <inttypes.h>

// GEANT4 //
#include "G4VUserDetectorConstruction.hh"
#include "G4Box.hh"
#include "G4Orb.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVParameterised.hh"

// USER //
#include "Cache.hh"
#include "CachedParameterisation.hh"
#include "DetectorConstructionMessenger.hh"


class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    DetectorConstruction();
    ~DetectorConstruction();

    G4VPhysicalVolume* Construct();
    bool UpdateParameterisation(G4ThreeVector position, bool force);

  public:
    void SetFilename(G4String filename) {
        G4cout << "Setting filename: " << filename << G4endl;
        this->filename = filename;
    };

    void SetDataset(G4String dataset) {
        G4cout << "Setting dataset: " << dataset << G4endl;
        this->dataset = dataset;
    };

    void SetCount(G4int count) {
        this->count = count;
    };

    void SetSmartless(G4double smartless) {
        this->smartless = smartless;
    };

    void SetLimit(G4double limit) {
        this->limit = limit;
    };

    void SetCacheSize(G4int size) {
        parameterisation_cache->SetSize(size);
    };

    void SetVerbosity(G4int verbose) {
        this->verbose = verbose;
    };

  public:
    G4Box* world_solid;
    G4LogicalVolume* world_logical;
    G4VPhysicalVolume* world_physical;

    Cache* parameterisation_cache;
    CachedParameterisation* parameterisation;
    G4PVParameterised* replication;

    G4String filename;
    G4String dataset;
    G4int count;
    G4double smartless;
    G4double limit;
    G4int verbose;

    DetectorConstructionMessenger* messenger;
};
#endif


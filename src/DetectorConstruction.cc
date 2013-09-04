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


#include <iostream>

// USER //
#include "DetectorConstruction.hh"

// GEANT4 //
#include "globals.hh"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4RunManager.hh"
#include "G4VVisManager.hh"
#include "G4VisAttributes.hh"
#include "G4UIcommand.hh"
#include "G4Orb.hh"
#include "G4UserLimits.hh"


DetectorConstruction::DetectorConstruction()
{
    this->filename = "";
    this->dataset = "";
    this->count = 0;
    this->smartless = 2.0;
    this->limit = 0;

    // Initialise LRU Cache
    parameterisation_cache = new Cache(10, 1.0);

    // Messenger
    messenger = new DetectorConstructionMessenger(this);
}


DetectorConstruction::~DetectorConstruction()
{
    delete messenger;
}


G4VPhysicalVolume* DetectorConstruction::Construct()
{
    G4NistManager* nist_manager = G4NistManager::Instance();
    G4Material* air = nist_manager->FindOrBuildMaterial("G4_AIR");
    G4Material* water = nist_manager->FindOrBuildMaterial("G4_WATER");

    world_solid = new G4Box("world_solid", 2*cm, 2*cm, 2*cm);
    world_logical = new G4LogicalVolume(world_solid, air, "world_logical", 0, 0, 0);
    world_physical = new G4PVPlacement(0, G4ThreeVector(), world_logical,
            "world_physical", 0, false, 0);
    world_logical->SetVisAttributes(G4VisAttributes::Invisible);
    world_logical->SetSmartless(smartless);

    // User Limits
    G4UserLimits* step_limit = new G4UserLimits(limit);
    world_logical->SetUserLimits(step_limit);

    parameterisation = new CachedParameterisation(filename, dataset);

    G4Orb* sphere_solid = new G4Orb("sphere", .1*mm);
    G4LogicalVolume* sphere_logical =
        new G4LogicalVolume(sphere_solid, air, "sphere", 0, 0, 0);

    replication = new G4PVParameterised("CachedParam",
            sphere_logical, world_logical, kUndefined,
            0, parameterisation, false);  
    
    // Set to 0 here, as it will be updated
    // in the stepping action.
    //replication->SetNoReplicas(count);    

    return world_physical;
}


bool DetectorConstruction::UpdateParameterisation(G4ThreeVector position)
{
    bool update;
    bool outside = parameterisation->OutsideOfCurrentRegion(position);
   
    if (outside) {
        G4cout << "DetectorConstruction::UpdateParameterisation OUTSIDE" << G4endl;

        CachedParameterisation* param = parameterisation_cache->pull(position);
        if (param == NULL) {
            G4cout << "DetectorConstruction::UpdateParameterisation NEW" << G4endl;
            param = new CachedParameterisation(*parameterisation);
            param->ComputeNeighbors(position, count);
            parameterisation_cache->push(position, param);
        } else {
            G4cout << "DetectorConstruction::UpdateParameterisation CACHED" << G4endl;
            parameterisation = param;
        }
        replication->SetNoReplicas(parameterisation->GetSize());
        update = true;
    } else {
        G4cout << "DetectorConstruction::UpdateParameterisation INSIDE" << G4endl;
        update = false;
    }
   
    if (update) { 
        G4RunManager::GetRunManager()->GeometryHasBeenModified();
        G4VVisManager::GetConcreteInstance()->GeometryHasChanged();
    }

    return update;
};


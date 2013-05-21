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
#include "G4VisAttributes.hh"
#include "G4UIcommand.hh"
#include "G4Orb.hh"
#include "G4PVParameterised.hh"


DetectorConstruction::DetectorConstruction(G4int count, G4double smartless)
{
    this->count = count;
    this->smartless = smartless;
}


DetectorConstruction::~DetectorConstruction()
{
}


G4VPhysicalVolume* DetectorConstruction::Construct()
{
    G4NistManager* nist_manager = G4NistManager::Instance();
    G4Material* air = nist_manager->FindOrBuildMaterial("G4_AIR");
    G4Material* water = nist_manager->FindOrBuildMaterial("G4_WATER");

    world_solid = new G4Box("world_solid", 200*cm, 200*cm, 200*cm);
    world_logical = new G4LogicalVolume(world_solid, air, "world_logical", 0, 0, 0);
    world_physical = new G4PVPlacement(0, G4ThreeVector(), world_logical,
            "world_physical", 0, false, 0);
    world_logical->SetVisAttributes(G4VisAttributes::Invisible);
    world_logical->SetSmartless(smartless);

    parameterisation = new CachedParameterisation("data.hdf5");

    G4Orb* sphere_solid = new G4Orb("sphere", 1*cm);
    G4LogicalVolume* sphere_logical =
        new G4LogicalVolume(sphere_solid, water, "sphere", 0, 0, 0);

    replication = new G4PVParameterised("CachedParam",
            sphere_logical, world_logical, kUndefined,
            0, parameterisation, false);  
    
    // Set to 0 here, as it will be updated
    // in the stepping action.
    //replication->SetNoReplicas(count);    

    return world_physical;
}


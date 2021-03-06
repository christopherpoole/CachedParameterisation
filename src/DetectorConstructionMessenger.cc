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


// USER //
#include "DetectorConstructionMessenger.hh"
#include "DetectorConstruction.hh"
#include "SteppingAction.hh"

// GEANT4 //
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithAString.hh"
#include "G4EventManager.hh"


DetectorConstructionMessenger::DetectorConstructionMessenger(DetectorConstruction* det)
        :detector_construction(det)
{ 
    command_directory = new G4UIdirectory("/CachedParam/");
    command_directory->SetGuidance("General commands for cached parameterisation.");

    set_filename = new G4UIcmdWithAString("/CachedParam/SetFilename", this);  
    set_filename->SetGuidance("Set the source data filename.");
    set_filename->SetParameterName("filename", false);
    set_filename->AvailableForStates(G4State_PreInit);  

    set_dataset = new G4UIcmdWithAString("/CachedParam/SetDataset", this);  
    set_dataset->SetGuidance("Set the source dataset in the HDF5 file.");
    set_dataset->SetParameterName("dataset", false);
    set_dataset->AvailableForStates(G4State_PreInit);  

    set_count = new G4UIcmdWithAnInteger("/CachedParam/SetCount", this);  
    set_count->SetGuidance("Set the maximum number of replicas to load into each voxel.");
    set_count->SetParameterName("count", false);
    set_count->SetRange("count >= 0");
    set_count->AvailableForStates(G4State_PreInit);  

    set_cache_size = new G4UIcmdWithAnInteger("/CachedParam/SetCacheSize", this);  
    set_cache_size->SetGuidance("Set the maximum number of entrys in the cache.");
    set_cache_size->SetParameterName("size", false);
    set_cache_size->SetRange("size >= 0");
    set_cache_size->AvailableForStates(G4State_PreInit);  

    set_smartless = new G4UIcmdWithADouble("/CachedParam/SetSmartless", this);  
    set_smartless->SetGuidance("Set the smartless for the replica mother volume.");
    set_smartless->SetParameterName("smartless", false);
    set_smartless->SetRange("smartless >= 0.0");
    set_smartless->AvailableForStates(G4State_PreInit);  

    set_limit = new G4UIcmdWithADoubleAndUnit("/CachedParam/SetLimit", this);  
    set_limit->SetGuidance("Set the forcing step limit.");
    set_limit->SetParameterName("limit", false);
    set_limit->SetUnitCategory("Length");
    set_limit->SetRange("limit > 0.0");
    set_limit->AvailableForStates(G4State_PreInit);  

    set_verbosity = new G4UIcmdWithAnInteger("/CachedParam/SetVerbosity", this);  
    set_verbosity->SetGuidance("Set the level of debug output to print.");
    set_verbosity->SetParameterName("verbosity", false);
    set_verbosity->SetRange("verbosity >= 0");
    set_count->AvailableForStates(G4State_PreInit);  

    dump_cache = new G4UIcmdWithAString("/CachedParam/DumpCache", this);  
    dump_cache->SetGuidance("Dump the parameterisation cache.");
    dump_cache->SetParameterName("operation", true);
    dump_cache->AvailableForStates(G4State_Idle);  
}


DetectorConstructionMessenger::~DetectorConstructionMessenger()
{
    delete set_filename;
    delete set_dataset;
    delete set_count;
    delete set_cache_size;
    delete set_smartless;
    delete set_limit;

    delete set_verbosity;

    delete dump_cache;
}


void DetectorConstructionMessenger::SetNewValue(G4UIcommand* command, G4String value)
{       
    if (command == set_filename)
        detector_construction->SetFilename(value);

    if (command == set_dataset)
        detector_construction->SetDataset(value);

    if (command == set_count) 
        detector_construction->SetCount(set_count->GetNewIntValue(value));

    if (command == set_cache_size) 
        detector_construction->SetCacheSize(set_count->GetNewIntValue(value));

    if (command == set_smartless)
        detector_construction->SetSmartless(set_smartless->GetNewDoubleValue(value));

    if (command == set_limit)
        detector_construction->SetLimit(set_limit->GetNewDoubleValue(value));

    if (command == set_verbosity) { 
        detector_construction->SetVerbosity(set_verbosity->GetNewIntValue(value));
        ((SteppingAction*) G4EventManager::GetEventManager()->GetUserSteppingAction())
            ->SetVerbosity(set_verbosity->GetNewIntValue(value));
    }

    if (command == dump_cache)
        detector_construction->parameterisation_cache->dump();
}


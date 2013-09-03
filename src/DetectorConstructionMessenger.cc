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

// GEANT4 //
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithAString.hh"


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
}


DetectorConstructionMessenger::~DetectorConstructionMessenger()
{
    delete set_filename;
    delete set_dataset;
    delete set_count;
    delete set_smartless;
    delete set_limit;
}


void DetectorConstructionMessenger::SetNewValue(G4UIcommand* command, G4String value)
{       
    if (command == set_filename)
        detector_construction->SetFilename(value);

    if (command == set_dataset)
        detector_construction->SetDataset(value);

    if (command == set_count) 
        detector_construction->SetCount(set_count->GetNewIntValue(value));

    if (command == set_smartless)
        detector_construction->SetSmartless(set_smartless->GetNewDoubleValue(value));

    if (command == set_limit)
        detector_construction->SetLimit(set_limit->GetNewDoubleValue(value));
}


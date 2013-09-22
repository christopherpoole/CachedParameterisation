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
#include "SteppingAction.hh"
#include "DetectorConstruction.hh"

// GEANT4 //
#include "G4SteppingManager.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4StepPoint.hh"
#include "G4TrackStatus.hh"
#include "G4RunManager.hh"

#include "Randomize.hh"


SteppingAction::SteppingAction()
{
    verbose = 0;
    last_position = G4ThreeVector();
}

SteppingAction::~SteppingAction()
{
}

void SteppingAction::UserSteppingAction(const G4Step* step)
{
    DetectorConstruction * detector_construction = (DetectorConstruction*)
        (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    
    G4ThreeVector current_position = step->GetPostStepPoint()->GetPosition();
    
    if (verbose >= 1) {
        double length = (last_position - current_position).mag();

        G4cout << G4endl << "SteppingAction::UserSteppingAction at "
                         << current_position << " -> " << length << "mm" << G4endl;
        
        last_position = current_position;
    }

    bool update = detector_construction->UpdateParameterisation(current_position);
    
    usleep(50000);
}


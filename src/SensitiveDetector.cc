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
#include "SensitiveDetector.hh"
#include "DetectorConstruction.hh"

// GEANT4 //
#include "globals.hh"
#include "G4ProcessType.hh"
#include "G4HCofThisEvent.hh"
#include "G4TouchableHistory.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4VProcess.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4SteppingManager.hh"
#include "G4ThreeVector.hh"


SensitiveDetector::SensitiveDetector(const G4String& name) : G4VSensitiveDetector(name)
{
}

SensitiveDetector::~SensitiveDetector()
{
}

void SensitiveDetector::Init()
{
}


void SensitiveDetector::ZeroHistograms()
{
}


void SensitiveDetector::Initialize(G4HCofThisEvent*)
{
}


G4bool SensitiveDetector::ProcessHits(G4Step* aStep, G4TouchableHistory* touchable) {
    const G4Track* aTrack = aStep->GetTrack();
    const G4String name = aTrack->GetDefinition()->GetParticleName();

    G4double energy_deposit = aStep->GetTotalEnergyDeposit();
    G4ThreeVector position = aTrack->GetPosition();

    G4cout << "HIT: "  << position << G4endl;
    G4cout << "     "  <<  aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName() << G4endl;
}


void SensitiveDetector::EndOfEvent(G4HCofThisEvent*)
{
}


void SensitiveDetector::clear()
{
}


void SensitiveDetector::PrintAll()
{
}

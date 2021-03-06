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
#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "PrimaryGeneratorAction.hh"
#include "SteppingAction.hh"

// GEANT4 //
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4StepLimiterBuilder.hh"

#include "Randomize.hh"

// Files
#include <fcntl.h>
#include <unistd.h>


//int main(int argc,char** argv)
int main(int, char** argv)
{
    CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine());

    G4long seed;
    G4long random_data = open("/dev/random", O_RDONLY);
        read(random_data, &seed, sizeof seed);
        close(random_data);
    CLHEP::HepRandom::setTheSeed(seed);

    G4RunManager* run_manager = new G4RunManager;

    DetectorConstruction* detector_construction = new DetectorConstruction();
    run_manager->SetUserInitialization(detector_construction);

    G4VModularPhysicsList* physics_list = new PhysicsList;
    physics_list->RegisterPhysics(new G4StepLimiterBuilder());
    run_manager->SetUserInitialization(physics_list);

    G4VUserPrimaryGeneratorAction* primary_generator = new PrimaryGeneratorAction;
    run_manager->SetUserAction(primary_generator);

    G4UserSteppingAction* stepping_action = new SteppingAction;
    run_manager->SetUserAction(stepping_action);

    G4VisManager* vis_manager = new G4VisExecutive;
    vis_manager->Initialize();

    G4UImanager* UI = G4UImanager::GetUIpointer();

    G4UIsession* session = new G4UIterminal(new G4UItcsh);
    G4String command = "/control/execute ";
    UI->ApplyCommand(command + argv[1]);
    //session->SessionStart();

    delete session;
    delete vis_manager;
    delete run_manager;

    return 0;
}



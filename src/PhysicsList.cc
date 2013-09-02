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
#include "PhysicsList.hh"

// GEANT4 //
#include "G4EmStandardPhysics_option1.hh"
#include "G4ProcessManager.hh"
#include "G4StepLimiter.hh"


PhysicsList::PhysicsList()
{
    em_physics = new G4EmStandardPhysics_option1();
}

PhysicsList::~PhysicsList()
{
    delete em_physics;
}

void PhysicsList::ConstructParticle()
{
    em_physics->ConstructParticle();
}

void PhysicsList::ConstructProcess()
{
    AddTransportation();
    em_physics->ConstructProcess();

    // Add step limiter
    G4StepLimiter* step_limiter = new G4StepLimiter();

    theParticleIterator->reset();
    while((*theParticleIterator)()) {
        G4ParticleDefinition* particle = theParticleIterator->value();
        G4ProcessManager* process_manager = particle->GetProcessManager();
        G4String particle_name = particle->GetParticleName();

        if (particle_name == "gamma") {
            process_manager->AddDiscreteProcess(step_limiter);
        } else if (particle_name == "e-") {
            process_manager->AddDiscreteProcess(step_limiter);
        } else if (particle_name == "e+") {
            process_manager->AddDiscreteProcess(step_limiter);
        }
    }
}

void PhysicsList::SetCuts()
{
    SetCutValue(0.1*mm, "gamma");
    SetCutValue(0.01*mm, "e-");
    SetCutValue(0.01*mm, "e+");
}


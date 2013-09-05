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


#ifndef DetectorConstructionMessenger_h
#define DetectorConstructionMessenger_h 1

// GEANT4 //
#include "G4UImessenger.hh"
#include "globals.hh"


class DetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithADouble;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;


class DetectorConstructionMessenger: public G4UImessenger
{
  public:
    DetectorConstructionMessenger(DetectorConstruction*);
   ~DetectorConstructionMessenger();
    
    virtual void SetNewValue(G4UIcommand*, G4String);
    
  private:
    DetectorConstruction* detector_construction;
    G4UIdirectory* command_directory;

    G4UIcmdWithAString* set_filename;
    G4UIcmdWithAString* set_dataset;
    G4UIcmdWithAnInteger* set_count;
    G4UIcmdWithAnInteger* set_cache_size;
    G4UIcmdWithADouble* set_smartless;
    G4UIcmdWithADoubleAndUnit* set_limit;
    
    G4UIcmdWithAString* dump_cache;
};

#endif


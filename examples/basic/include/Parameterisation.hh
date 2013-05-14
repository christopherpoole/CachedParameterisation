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


#ifndef CACHEDPARAMETERISATOIN_H
#define CACHEDPARAMETERISATOIN_H


// GEANT4 //
#include "globals.hh"
#include "Randomize.hh"

// CachedParameterisation //
#include "CachedParameterisation.hh"


class Parameterisation : public CachedParameterisation{
  public:
    Parameterisation() {};
    ~Parameterisation() {};

  public:
    void ComputeTransformation (const G4int copy_number,
            G4VPhysicalVolume* physical_volume) const
    {
        G4ThreeVector origin(20*G4UniformRand()*cm,
                20*G4UniformRand()*cm,
                20*G4UniformRand()*cm);
        physical_volume->SetTranslation(origin);
    };
 
    void ComputeDimensions(G4Orb& physical_volume, const G4int copy_number,
            const G4VPhysicalVolume*) const
    {
        physical_volume.SetRadius(G4UniformRand()*mm);
    };
    
    //G4Material* ComputeMaterial(G4VPhysicalVolume *physical_volume,
    //        const G4int copy_number, const G4VTouchable *parent_touchable) {
    //};
 
};

#endif // CACHEDPARAMETERISATOIN_H


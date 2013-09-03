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


#ifndef HELPERS_HH
#define HELPERS_HH

// GEANT4 //
#include "globals.hh"
#include "G4ThreeVector.hh"

// SpatialIndex //
#include "spatialindex/SpatialIndex.h"
#include "spatialindex/Region.h"


namespace Helpers {

G4ThreeVector PointToG4ThreeVector(SpatialIndex::Point point);
SpatialIndex::Point G4ThreeVectorToPoint(G4ThreeVector vector);

G4ThreeVector GetLowerPointAsG4ThreeVector(SpatialIndex::Region region);
G4ThreeVector GetUpperPointAsG4ThreeVector(SpatialIndex::Region region);

}

#endif // HELPERS_H


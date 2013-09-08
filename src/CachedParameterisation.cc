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
#include "CachedParameterisation.hh"


CachedParameterisation::CachedParameterisation(G4String filename, G4String dataset)
{
    this->do_transform = true;
    this->do_dimensions = false;

    this->neighbourhood = new Neighbourhood(filename, dataset);
    this->size = neighbourhood->GetSize();
}


CachedParameterisation::CachedParameterisation(CachedParameterisation& other) 
{
    x = std::vector<double>(other.x);
    y = std::vector<double>(other.y);
    z = std::vector<double>(other.z);
    r = std::vector<double>(other.r);

    neighbourhood = other.neighbourhood;
}


CachedParameterisation::~CachedParameterisation()
{
}


void CachedParameterisation::ComputeTransformation(const G4int copy_number,
        G4VPhysicalVolume* physical_volume) const
{
    G4double x = this->x[copy_number];
    G4double y = this->y[copy_number];
    G4double z = this->z[copy_number];
    
    G4ThreeVector origin = G4ThreeVector(x, y, z);
    physical_volume->SetTranslation(origin);
}


G4Material* CachedParameterisation::ComputeMaterial(G4VPhysicalVolume *physical_volume,
            const G4int copy_number, const G4VTouchable *parent_touchable) {
}; 


bool CachedParameterisation::OutsideOfCurrentRegion(G4ThreeVector position) {
    if (this->x.size() > 0) { 
        return neighbourhood->OutsideOfCurrentRegion(position);
    }
    return true;
}

void CachedParameterisation::ComputeNeighbors(G4ThreeVector position, G4int number) {
    Visitor visitor = neighbourhood->ComputeNeighbours(position, number);
    this->x = visitor.x;
    this->y = visitor.y;
    this->z = visitor.z;

    this->size = x.size();
};


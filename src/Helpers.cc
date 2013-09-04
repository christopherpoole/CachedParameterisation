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


// USER
#include "Helpers.hh"

namespace Helpers {

G4ThreeVector PointToG4ThreeVector(SpatialIndex::Point point) {
    return G4ThreeVector(point.getCoordinate(0),
                         point.getCoordinate(1),
                         point.getCoordinate(2));
}


SpatialIndex::Point G4ThreeVectorToPoint(G4ThreeVector vector) {
    double p[3];
    p[0] = vector.x();
    p[1] = vector.y();
    p[2] = vector.z();

    return SpatialIndex::Point(p, 3);
}


SpatialIndex::Point GetLowerPoint(SpatialIndex::Region region) {
    unsigned int dim = region.getDimension();
    std::vector<double> p;

    for (unsigned int i=0; i<dim; i++) {
        p.push_back(region.getLow(i));
    }

    return SpatialIndex::Point(&p[0], dim);    
}


SpatialIndex::Point GetUpperPoint(SpatialIndex::Region region) {
    unsigned int dim = region.getDimension();
    std::vector<double> p;

    for (unsigned int i=0; i<dim; i++) {
        p.push_back(region.getHigh(i));
    }

    return SpatialIndex::Point(&p[0], dim);    
}


G4ThreeVector GetLowerPointAsG4ThreeVector(SpatialIndex::Region region) {
    // TODO: Assert region.dim == 3
    return PointToG4ThreeVector(GetLowerPoint(region));
}


G4ThreeVector GetUpperPointAsG4ThreeVector(SpatialIndex::Region region) {
    // TODO: Assert region.dim == 3
    return PointToG4ThreeVector(GetUpperPoint(region));
}


G4ThreeVector GetCenterAsG4ThreeVector(SpatialIndex::Region region) {
    SpatialIndex::Point point;
    region.getCenter(point);

    return PointToG4ThreeVector(point);
}


SpatialIndex::Point FindBound(const double& (*f)(const double&, const double&),
                                   SpatialIndex::Point first, SpatialIndex::Point second) {
    // TODO: Assert first.dimension == second.dimesion
    
    unsigned int dim = first.getDimension();
    std::vector<double> p;

    for (unsigned int i=0; i<dim; i++) {
        double coordinate = (*f)(first.getCoordinate(i), second.getCoordinate(i));
        p.push_back(coordinate);
    }
    
    return SpatialIndex::Point(&p[0], dim);
}


SpatialIndex::Point FindLowerBound(SpatialIndex::Point first, SpatialIndex::Point second) {
    return FindBound(std::min, first, second);
}


SpatialIndex::Point FindUpperBound(SpatialIndex::Point first, SpatialIndex::Point second) {
    return FindBound(std::max, first, second);
}

}


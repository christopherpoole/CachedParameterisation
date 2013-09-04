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


#ifndef Cache_h
#define Cache_h 1

// GEANT4 //
#include "globals.hh"

// LRU Cache
#include "lru_cache.h"

// USER //
#include "Helpers.hh"
#include "CachedParameterisation.hh"


class Cache 
{
  public:
    Cache(unsigned int size) {
        this->size = size;

        lru_cache = new LRUCache<G4ThreeVector, CachedParameterisation*>(size);
    };

    ~Cache() {
    };

  public:
    unsigned int size;

    LRUCache<G4ThreeVector, CachedParameterisation*>* lru_cache;
};

#endif


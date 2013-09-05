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

// USER //
#include "Helpers.hh"


template<class K, class V>
class CacheBase
{
  public:
    CacheBase(unsigned int max_size) {
        this->max_size = max_size;

        index = new std::list<K>();
        cache = new std::map<K, V>();
    };

    ~CacheBase() {
        delete index;
        delete cache;
    };

    virtual void push(K key, V value) {
        G4cout << "Cache::push " << key << G4endl;

        // Remove if K:V exists
        pop(key);
        
        // Put K:V at the top of the list
        cache->insert(std::make_pair(key, value));
        index->push_front(key);
       
        // If the cache is oversize, remove the least used K:V 
        if (index->size() > max_size) {
            pop(index->back());
        }
    };

    virtual V pull(K key) {
        G4cout << "Cache::pull " << key << G4endl;

        if (exists(key)) {
            return cache->at(key);
        } else {
            return NULL;
        }
    };

    virtual void pop(K key) {
        G4cout << "Cache::pop " << key << G4endl;

        if (exists(key)) {
            cache->erase(key);
            index->remove(key);
        }
    };

    bool exists(K key) {
        G4cout << "Cache::exists " << key << G4endl;

        return cache->find(key) != cache->end();
    };

  protected:
    unsigned int max_size;

    std::list<K>* index;
    std::map<K, V>* cache;
};


#include <limits>
#include "CachedParameterisation.hh"


class Cache : public CacheBase<G4ThreeVector, CachedParameterisation*>
{
  public:
    Cache(unsigned int max_size, double threshold) : CacheBase(max_size) {
        this->threshold = threshold;
    }; 

    CachedParameterisation* pull(G4ThreeVector key) {
        G4ThreeVector nearest = nearest_key(key);
  
        if (nearest == key) {
            return NULL;
        } else {
            return CacheBase::pull(nearest);
        }
    };

    G4ThreeVector nearest_key(G4ThreeVector key) {
        // TODO: use a KD-tree instead of testing each key.
        // Find the closest key that is within this->threshold
        
        double distance = std::numeric_limits<double>::infinity();
        G4ThreeVector nearest = G4ThreeVector();

        for (std::list<G4ThreeVector>::iterator it=index->begin();
                                                it!=index->end(); ++it) {
            double d = (key - *it).mag();
            if (d <= threshold) {
                nearest = *it;
                distance = d;
                break;
            }
        }

        if (distance <= threshold) {
            return nearest;
        } else {
            return key; 
        }
    };

    void dump() {
        for (std::list<G4ThreeVector>::iterator it=index->begin();
                                                it!=index->end(); ++it) {
            G4cout << "Entry: " << *it << G4endl; 

            CachedParameterisation* param = CacheBase::pull(*it);
            for (unsigned int i=0; i<param->GetSize(); i++) {
                G4cout << "   " << param->GetPosition(i) << G4endl;
            }
        } 
    };

  private:
    double threshold;
};

#endif


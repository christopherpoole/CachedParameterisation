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


#ifndef DataStream_h
#define DataStream_h 1

// GEANT4 //
#include "globals.hh"

// SpatialIndex //
#include "spatialindex/SpatialIndex.h"
#define INSERT 1
#define DELETE 0
#define QUERY 2

// G4VoxelData //
#include "G4VoxelData.hh"
#include "G4VoxelArray.hh"
#include "HDF5MappedIO.hh"


class DataStream: public SpatialIndex::IDataStream
{
  public:
	DataStream(G4String filename)
	{
        transform = new HDF5MappedIO<int>();
        transform->Read(filename, "transform");

        copy_number = 0;
		readNextEntry();
	}

	virtual ~DataStream()
	{
	}

	virtual SpatialIndex::IData* getNext()
	{
		if (m_pNext == 0) return 0;

        SpatialIndex::RTree::Data* ret = m_pNext;
		m_pNext = 0;
		readNextEntry();
		return ret;
	}

	virtual bool hasNext()
	{
		return (m_pNext != 0);
	}

	virtual uint32_t size()
	{
	    return transform->GetShape()[0];
    }

	virtual void rewind()
	{
		if (m_pNext != 0)
		{
			delete m_pNext;
			m_pNext = 0;
		}

		copy_number = 0;
        readNextEntry();
	}

	void readNextEntry()
	{
		double low[3], high[3];
        
        // Calculate bounding box of replica 
        G4double delta = 0.1;
        G4int x = transform->GetValue(copy_number, 0)*cm;
        low[0] = x - delta; high[0] = x + delta;

        G4int y = transform->GetValue(copy_number, 1)*cm;
        low[1] = y - delta; high[1] = y + delta;
        
        G4int z = transform->GetValue(copy_number, 2)*cm;
        low[2] = z - delta; high[2] = z + delta;

        SpatialIndex::Region r(low, high, 3);
        m_pNext = new SpatialIndex::RTree::Data(0, 0, r, copy_number);

        copy_number++;
	}

  private:
    // Cached data files stored by copy number // 
    HDF5MappedIO<int>* transform;
    SpatialIndex::RTree::Data* m_pNext;

    G4int copy_number;    
};

#endif


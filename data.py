import sys

import numpy
import h5py


count = int(sys.argv[1])

f = h5py.File("data.hdf5")
d = f.create_dataset('transform', (3, count), int, chunks=(1, 2))
d[...] = numpy.random.random((3, count))*100
f.close()


import numpy
import h5py


f = h5py.File("data.hdf5")
d = f.create_dataset('transform', (3, 10), int, chunks=(1, 2))
d[...] = numpy.arange(30).reshape((3, 10))
f.close()


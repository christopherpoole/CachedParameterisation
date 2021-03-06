import sys

import numpy
import h5py


chunks = int(sys.argv[1])
count = int(sys.argv[2])
ndim = int(sys.argv[3])
spacing = float(sys.argv[4])

#coords = zip(
#             *map(
#                lambda x: x.flatten(),
#                numpy.mgrid[
#                    numpy.repeat(
#                        slice(-count, count+1), ndim
#                    )
#                ] * spacing
#             )
#         )

f = h5py.File("data.hdf5")
d = f.create_dataset('transform', (count*chunks, ndim), float, chunks=(chunks, 1))
d[...] = (numpy.random.random((count*chunks, ndim))*spacing) - (spacing/2.)
#d[...] = coords
f.close()


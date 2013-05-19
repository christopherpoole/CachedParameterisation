import pickle

import numpy

from matplotlib import rc
rc('text', usetex=True)
rc('font', family='serif')
import pylab


smart_vox = pickle.load(file("v_smart_vox"))
smart_mem = pickle.load(file("v_smart_mem"))
count_vox = pickle.load(file("v_count_vox"))
count_mem = pickle.load(file("v_count_mem"))


colors = 'rgbk'
pylab.figure()

colors = 'rgbk'
smartless = [0, 1, 2, 4]
for i, s in enumerate(smartless):
    xy = sorted([(kv[0], kv[1][i]) for kv in count_vox.items() if len(kv[1]) > i])
    pylab.plot([x[0] for x in xy], [y[1]*1024 for y in xy], color=colors[i],
        linestyle='--', marker='.')
    
    xy = sorted([(kv[0], kv[1][i]) for kv in count_mem.items() if len(kv[1]) > i])
    pylab.plot([x[0] for x in xy], [y[1]*1024 for y in xy], color=colors[i],
        marker='.', label="smartless = %i" % s)

pylab.legend(loc='lower right')
pylab.title("Resident memory (--), smartvoxel memory (- -) versus solid count.")
pylab.xlabel("$n$ parameterisations")
pylab.ylabel("Memory ($bytes$)")

pylab.loglog()
pylab.grid()
pylab.show()

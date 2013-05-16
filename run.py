from subprocess import Popen, PIPE
from collections import defaultdict

v_smart_vox = defaultdict(list)
v_smart_mem = defaultdict(list)
v_count_vox = defaultdict(list)
v_count_mem = defaultdict(list)

for count in [1, 10, 100, 1000, 10000, 100000, 1000000]:
    for smart in [0, 1, 2, 4, 8]:
        p = Popen(str("/usr/bin/time -v ./build/CachedParam %i %f" % (count, smart)).split(),
                stdout=PIPE, stderr=PIPE)

        output = p.stdout.readlines()[-23].strip().split()[3]
        stats = p.stderr.readlines()[9].split(':')[-1].strip()

        v_smart_vox[smart].append(int(output[:-1]))
        v_smart_mem[smart].append(int(stats))
        v_count_vox[count].append(int(output[:-1]))
        v_count_mem[count].append(int(stats))


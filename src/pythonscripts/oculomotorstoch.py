# ---------------------------------------------------------------------------//
#  Copyright (c) 2017 Eleftherios Avramidis <el.avramidis@gmail.com>
#
#  Distributed under The MIT License (MIT)
#  See accompanying file LICENSE.txt
# ---------------------------------------------------------------------------//

import numpy
import numpy.matlib
import random
import sodecl
import time

if __name__ == '__main__':
#def runbench(orbits):

    start = time.time()

    orbits = 8

    openclplatform = 1
    opencldevice = 0
    openclkernel = 'kernels/broomhead.cl'
    solver = 0
    nequat = 6
    nparams = 9
    nnoi = 3
    dt = 1e-8
    tspan = 0.1
    ksteps = 40000
    localgroupsize = 0

    initx = numpy.array([0, 0, 0, 0, 0, 0.7])
    initx = numpy.matlib.repmat(initx, orbits, 1)

    # low_bounds = [1, 0.1, 0.1, 0, 1, 0.1, 0, 0, 0]
    # upper_bounds = [1000, 60, 0.0001, 12, 1000, 60, 0.5, 0.1, 100]

    # low_bounds = [1, 0.1, 0.1, 0, 1, 0.1, 0, 0, 0]
    # upper_bounds = [1000, 60, 0.0001, 12, 1000, 60, 0, 0, 0]

    # low_bounds = [120, 1.5, 0.0045, 0.05, 600, 9, 0, 0, 0]
    # upper_bounds = [120, 1.5, 0.0045, 0.05, 600, 9, 0.5, 0.1, 100]

    low_bounds = [120, 1.5, 0.0045, 0.05, 600, 9, 0, 0, 0]
    upper_bounds = [120, 1.5, 0.0045, 0.05, 600, 9, 0, 0, 0]

    params = numpy.ndarray((orbits, nparams))
    for o in range(orbits):
        for p in range(nparams):
            params[o][p] = random.uniform(low_bounds[p], upper_bounds[p])

    # params = numpy.array([120, 1.5, 0.0045, 0.05, 600, 9, 0, 0, 0])
    # params = numpy.matlib.repmat(params, orbits, 1)

    sodecl.sodecl(openclplatform, opencldevice, openclkernel,
                  initx, params, solver,
                  orbits, nequat, nnoi,
                  dt, tspan, ksteps, localgroupsize)

    f = open("sodecloutput.bin", "r")
    a = numpy.fromfile(f, dtype=numpy.float)
    a = a.reshape(orbits*6, int(a.shape[0] / (orbits*6)), order='F')

    end = time.time()
    print("Simulation execution time: ", end - start, " seconds.")

    # print("NaN present: " + str(numpy.isnan(numpy.sum(numpy.sum(a)))))

    if numpy.isnan(numpy.sum(numpy.sum(a))):
        raise RuntimeError("NaN present!")

    import matplotlib.pyplot as plt
    plt.plot(a[0, :])
    # plt.plot(a)
    plt.ylabel('some numbers')
    plt.show()
    # return end - start

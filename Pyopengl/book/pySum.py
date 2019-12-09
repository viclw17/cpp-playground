def pySum():
    a = list(range(1000))
    b = list(range(1000))
    c = []
    for i in range(len(a)):
        c.append(a[i]**2 + b[i]**2)
    return c

import numpy as np
def npSum():
    a = np.arange(1000)
    b = np.arange(1000)
    c = a**2 + b**2
    return c

import timeit
print ('pyNum run 1000 times: ' + str(timeit.timeit(pySum,number=1000)))
print ('npNum run 1000 times: ' + str(timeit.timeit(npSum,number=1000)))

cpdef int twoSum(list lst):
    cdef set s = set(lst)
    print len(s)
    cdef int a = 0
    for target in xrange(-10000, 10000):
        for item in s:
            if target - item in s and target - item != item:
                a += 1
                break

    return a


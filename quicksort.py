from random import randrange

def partition(lst, l, r):             #First element is pivot, inplace
    i = l
    for j in xrange(l,r-1):
        if lst[j+1] < lst[l]:
            swap(lst, i+1, j+1)
            i+=1

    swap(lst, i, l)
    return i

def quickSort(lst, l, r):         #inplace
    if r <= l+1:
        return
    swap(lst, l, randrange(l, r))
    i = partition(lst, l, r)
    quickSort(lst, l, i)
    quickSort(lst, i+1, r)

def sort(lst):
    quickSort(lst, 0, len(lst))

def swap(lst, a, b):
    if a==b:
        return
    lst[a], lst[b] = lst[b], lst[a]
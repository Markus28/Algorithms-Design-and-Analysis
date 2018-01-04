from random import randrange

def rSelect(lst, l, r, k):
    if r==l+1:
        return lst[l]
    swap(lst, l, randrange(l, r))
    i = partition(lst, l, r)
    if i+1-l>k:
        return rSelect(lst, l, i, k)
    if i+1-l<k:
        return rSelect(lst, i+1, r, k-(i+1-l))
    return lst[i]
    
def partition(lst, l, r):             #First element is pivot, inplace
    i = l
    for j in xrange(l,r-1):
        if lst[j+1] < lst[l]:
            swap(lst, i+1, j+1)
            i+=1

    swap(lst, i, l)
    return i
  
def swap(lst, a, b):
    if a==b:
        return
    lst[a], lst[b] = lst[b], lst[a]

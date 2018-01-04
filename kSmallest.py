def kSmallest(lst, k):
    if len(lst) == 1:
        return lst
    
    lst1 = kSmallest(lst[0:len(lst)/2], k)
    lst2 = kSmallest(lst[len(lst)/2:], k)

    i = 0
    n = 0
    merged = []
    
    while (i+n)<k and i<len(lst1) and n<len(lst2):
        if lst1[i] < lst2[n]:
            merged.append(lst1[i])
            i += 1
        else:
            merged.append(lst2[n])
            n += 1

    merged += lst2[n:k-i]
    merged += lst1[i:k-n]
    
    return merged

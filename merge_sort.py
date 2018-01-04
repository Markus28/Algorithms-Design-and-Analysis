def sort(lst):
    if len(lst) == 1:
        return lst

    lst1 = sort(lst[0:len(lst)/2])
    lst2 = sort(lst[len(lst)/2:])

    i = 0
    n = 0
    merged = []
    
    while i<len(lst1) and n<len(lst2):
        if lst1[i] < lst2[n]:
            merged.append(lst1[i])
            i += 1;
        else:
            merged.append(lst2[n])
            n += 1;

    merged += lst2[n:]
    merged += lst1[i:]

    return merged

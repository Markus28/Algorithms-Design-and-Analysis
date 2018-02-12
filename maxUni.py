def maxUni(uni):
    if len(uni) == 1:
        return uni[0]

    if uni[len(uni)/2-1]<uni[len(uni)/2]:
        return maxUni(uni[len(uni)/2:])
    return maxUni(uni[0:len(uni)/2])
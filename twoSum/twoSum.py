import pyximport

pyximport.install()

from fastsum import *

with open("sum.txt", "r") as f:
    l = [int(item.strip()) for item in f.readlines()]

print twoSum(l)



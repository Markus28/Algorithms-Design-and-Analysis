import time

class Node:
    def __init__(self, label, adjacencies, index):
        self.label = label
        self.adjacencies = adjacencies
        self.distance = float("Inf")
        self.previous = None
        self.index = index

    def resetDistance(self, node):
        if node.distance + node.adjacencies[self.label] < self.distance:
            self.distance = node.distance + node.adjacencies[self.label]
            self.previous = node

    def getPath(self):
        if self.previous is not None:
            return self.previous.getPath()+[self.label]
        return []

    def __cmp__(self, other):
        return cmp(self.distance, other.distance)
   

class WeightedGraph:
    def __init__(self, adjacency_dict):
        self.adjacency_dict = adjacency_dict

    def path(self, a, b):
        unvisited = [Node(key, self.adjacency_dict[key], index) for index, key in enumerate([key for key in self.adjacency_dict.keys() if key != a])]
        unvisited_map = {key: value for (key, value) in [(node.label, node) for node in unvisited]}
        
        current = Node(a, self.adjacency_dict[a],0)
        current.distance = 0
        return self._path_primed(b, unvisited, unvisited_map, current)

    def _path_primed(self, b, unvisited, unvisited_map, current, pops = 0):
        for next_vertex in current.adjacencies.keys():
            try:
                unvisited_map[next_vertex].resetDistance(current)
                siftdown(unvisited, pops, unvisited_map[next_vertex].index)
            except KeyError as e:
                pass

        current = unvisited[pops]
        unvisited_map.pop(current.label)
        
        if current.label == b:
            return current

        elif current.distance == float("Inf"):
            return None
        
        return self._path_primed(b, unvisited, unvisited_map, current, pops = pops+1)

            

def siftdown(heap, startpos, pos):
    pos_calc = pos - startpos
    parentpos = (pos_calc-1)/2 + startpos
    while parentpos >= startpos and heap[pos] < heap[parentpos]:
        heap[pos], heap[parentpos] = heap[parentpos], heap[pos]
        heap[pos].index = pos
        heap[parentpos].index = parentpos
        pos = parentpos
        pos_calc = pos - startpos
        parentpos = (pos_calc-1)/2 + startpos
        
        

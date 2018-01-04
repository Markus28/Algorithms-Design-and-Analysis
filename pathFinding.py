import heapq


class Node:
    def __init__(self, label, adjacencies):
        self.label = label
        self.adjacencies = adjacencies
        self.distance = float("Inf")
        self.path = []

    def resetDistance(self, node):
        if node.distance + node.adjacencies[self.label] < self.distance:
            self.distance = node.distance + node.adjacencies[self.label]
            self.path = node.path[:]
            self.path.append(node.label)

    def __cmp__(self, other):
        return cmp(self.distance, other.distance)



class WeightedGraph:
    def __init__(self, adjacency_dict):
        self.adjacency_dict = adjacency_dict

    def path(self, a, b):
        unvisited = [Node(key, self.adjacency_dict[key]) for key in self.adjacency_dict.keys() if key != a]
        unvisited_map = {}
        
        for node in unvisited:
            unvisited_map[node.label] = node
            
        heapq.heapify(unvisited)
        
        current = Node(a, self.adjacency_dict[a])
        current.distance = 0
        return self._path_primed(b, unvisited, unvisited_map, current)

    def _path_primed(self, b, unvisited, unvisited_map, current):
        for next_vertex in current.adjacencies.keys():
            try:
                unvisited_map[next_vertex].resetDistance(current)
            except:
                pass

        heapq.heapify(unvisited)
        current = heapq.heappop(unvisited)
        unvisited_map.pop(current.label)
        
        if current.label == b:
            return current

        elif current.distance == float("Inf"):
            return None
        
        return self._path_primed(b, unvisited, unvisited_map, current)
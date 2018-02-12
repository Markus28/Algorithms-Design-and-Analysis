import random

def choice_weighted(lst, lst_probs):
    lst_sum = [0]
    for prob in lst_probs:
        lst_sum.append(lst_sum[-1]+prob)

    a = random.uniform(0, lst_sum[-1])
    for i in range(1, len(lst_sum)):
        if lst_sum[i] > a:
            return lst[i-1]

        
class UndirectedUnweightedGraph:
    def __init__(self, adjacency_dict):                       #Expects dictionary in which the keys are labels of vertices, the corresponding values are lists of adjacent vertices
        self.adjacency_dict = adjacency_dict
        if not self.checkGraph():
            raise Exception("Graph is corrupted...")


    def checkGraph(self):
        for key in self.adjacency_dict.keys():
            for n in self.adjacency_dict[key]:
                if not key in self.adjacency_dict[n]:
                    return False
        return True

    def minCut(self, inPlace = False):
        if not inPlace:
            copy = UndirectedUnweightedGraph(dict(self.adjacency_dict))
            return copy.minCut(True)

        while len(self.adjacency_dict.keys()) > 2:
            keys = self.adjacency_dict.keys()
            v1 = choice_weighted(keys, [len(self.adjacency_dict[key]) for key in keys])
            v2 = random.choice(self.adjacency_dict[v1])
            self.fuseVertices(v1, v2, (v1, v2))

        return self.adjacency_dict

        
    def fuseVertices(self, v1, v2, v3):                       #Old labels of vertices and new label of fused vertex
        v1_neighbours = self.adjacency_dict.pop(v1)
        v2_neighbours = self.adjacency_dict.pop(v2)
        self.adjacency_dict[v3] = filter(lambda x: x != v2, v1_neighbours) + filter(lambda x: x != v1, v2_neighbours)
        for vertex in self.adjacency_dict[v3]:
            self.adjacency_dict[vertex] = map(lambda x: v3 if x in (v1, v2) else x, self.adjacency_dict[vertex])
            

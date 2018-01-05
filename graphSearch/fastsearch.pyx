cdef class Node:
    cdef public int label, n, f_time, level
    cdef readonly int cluster
    cdef readonly list adjacency_list, path
    cdef public bint explored
    
    def __init__(self, int label):
        self.label = label
        self.adjacency_list = []
        self.explored = False
        self.path = []
        self.level = -1
        self.cluster = -1
        self.n = -1
        self.f_time = -1

    def explore(self, int cluster_label):
        self.explored = True
        self.cluster = cluster_label

    def setAdjacencyList(self, list lst):
        self.adjacency_list = lst

    def setPath(self, Node node):
        self.path = node.path[:]
        self.path.append(node.label)
        self.level = len(self.path)

    def flush(self):
        self.explored = False
        self.path = []
        self.level = -1
        self.cluster = -1
        self.n = -1
        self.f_time = -1


cpdef tuple dfs_primed(Node s, int cluster_label, int n = 0, int f = 0):
        s.explore(cluster_label)
        for next_vertex in s.adjacency_list:
            if not next_vertex.explored:
                n,f = dfs_primed(next_vertex, cluster_label, n, f)

        s.n = n
        s.f_time = f
        f += 1
        n -= 1
        
        return n,f 

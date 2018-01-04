from collections import deque, defaultdict
import sys
import pyximport

pyximport.install()

from fastsearch import Node, dfs_primed


     
class UnweightedGraph:
    def __init__(self, adjacency_dict):
        self.adjacency_dict = adjacency_dict
        self.nodes = [Node(label) for label in self.adjacency_dict.keys()]
        self.node_map = {key: value for (key, value) in zip([node.label for node in self.nodes], self.nodes)}
        for node in self.nodes:
            node.setAdjacencyList([self.node_map[label] for label in self.adjacency_dict[node.label]])

    def bfs(self, s, cluster_label = -1):
        origin = self.node_map[s]
        origin.level = 0
        origin.explore(cluster_label)
        queue = deque([origin])
        self._bfs_primed(queue, cluster_label)
        return_lst = [(node.label, node.explored, node.cluster, node.path) for node in self.nodes]
        self.flush()
        return return_lst

    def dfs(self, s, cluster_label = -1):
        origin = self.node_map[s]
        dfs_primed(origin, cluster_label)
        return_lst = [(node.label, node.cluster, node.explored) for node in self.nodes]
        self.flush()
        return return_lst


    def sortTopologically(self):
        if len(self.findSCC()) != len(self.adjacency_dict.keys()):
            raise Exception("Graph contains cycles...")
        start = self.adjacency_dict.keys()[0]
        origin = self.node_map[start]
        n = len(self.adjacency_dict.keys())
        n = dfs_primed(origin,self.nodes, -1, n = n)[0]
        for node in self.nodes:
            if not node.explored:
                n = dfs_primed(node, -1, n=n)[0]

        return_lst = [(node.label, node.n) for node in self.nodes]
        self.flush()
        return return_lst

    def findSCC(self):
        print "Creating reverse Graph..."
        reverse_graph_dict = defaultdict(list)
        for key in self.adjacency_dict.keys():
            reverse_graph_dict[key]
            for vertex in self.adjacency_dict[key]:
                reverse_graph_dict[vertex].append(key)

        reverse_graph_dict.default_factory = None
        cp_reverse = UnweightedGraph(reverse_graph_dict)
        f = 0
        sorted_by_f = [None,]*len(self.nodes)
        print "First pass..."
        for node in cp_reverse.nodes:
            if not node.explored:
                f = dfs_primed(node, -1, 0, f)[1]
            sorted_by_f[len(self.nodes)-node.f_time-1] = node.label

        scc_count = 0
        print "Second pass..."
        for node in sorted_by_f:
            if not self.node_map[node].explored:
                dfs_primed(self.node_map[node], scc_count)
                scc_count += 1

        print "Ordering clusters..."
        sccs = [[] for _ in range(scc_count)]
        for node in self.nodes:
            sccs[node.cluster].append(node.label)

        self.flush()

        return sorted(sccs, key = lambda x: len(x), reverse = True)

    
    def _bfs_primed(self, queue, cluster_label):
        while len(queue) != 0:
            to_be_explored = queue.popleft()
            for next_vertex in to_be_explored.adjacency_list:
                if not next_vertex.explored:
                    next_vertex.setPath(to_be_explored)
                    next_vertex.explore(cluster_label)
                    queue.append(next_vertex)


    def flush(self):
        for node in self.nodes:
            node.flush()


d = defaultdict(list)

with open("SCC.txt", "r") as f:
    lines = (line.strip().split() for line in f)
    for line in lines:
        d[int(line[1])]
        d[int(line[0])].append(int(line[1]))

d.default_factory = None
print "Computing SCCs..."
g = UnweightedGraph(d)
print [len(item) for item in g.findSCC()[:7]]




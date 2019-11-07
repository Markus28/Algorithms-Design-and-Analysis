#include <iostream>
#include <vector>
#include <tuple>
#include <cassert>
#include <algorithm>

using edge = std::tuple<unsigned int, unsigned int, unsigned int>;

bool compare_edges(edge a, edge b){
    return std::get<2>(a)<std::get<2>(b);
}


/*
 * This class represents a vertex in the graph. Every node is part of subgraph which is connected by the MST
 * which is being built. Note, that this is an equivalence relation. We refer to a chosen representative of a
 * equivalence class (i.e. the by the MST connected component) as the "root".
 * The nodes are organized into a forest of trees with every node pointing toward its root (i.e. representative) and
 * every tree being a connected component (by the MST).
 *
 * If a new edge is added to the MST, two connected components (represented as trees) are merged. This is done
 * with merge(const KruskalVertex& other). merge ensures that the trees remain balanced.
 */
class KruskalVertex{
public:
    KruskalVertex(unsigned int label): parent(nullptr), height(0), label(label) {};

    KruskalVertex(const KruskalVertex& other) {
        assert(other.parent== nullptr);             //We do not want to copy pointers!
        height = other.height;
        label = other.label;
        parent = nullptr;
    }

    KruskalVertex& operator=(const KruskalVertex& other) {
        assert(other.parent == nullptr);            //We do not want to copy pointers
        height = other.height;
        label = other.label;
        parent = nullptr;
        return *this;
    }

    bool is_root(){
        return parent == nullptr;
    }

    void merge(KruskalVertex& other){
        assert(other.is_root() && is_root());
        if(height>=other.height){
            other.parent = this;
            height = std::max(height, other.height+1);
        }
        else{
            parent = &other;
            other.height = std::max(other.height, height+1);
        }
    }

    unsigned int get_root_label(){
        if(parent== nullptr){
            return label;
        }
        return parent->get_root_label();
    }

private:
    KruskalVertex* parent;
    unsigned int height;
    unsigned int label;
};


/*
 * This function will find the MST of a graph, edges.
 * edges must be a connected graph consisting of vertices labeled with unsigned integers from 0 to n (inclusive).
 * All integers from 0 to n (inclusive) must be used.
 * An edge e in edges has the form e = (x,y,w) where x and y are the labels (unsigned int) of the vertices which are
 * connected by e and w (unsigned int) is the weight of e.
 * The function returns a subset of edges, the MST.
 */
std::vector<edge> kruskal(std::vector<edge> edges, unsigned int n){
    auto ordered_eges = edges;
    std::sort(ordered_eges.begin(), ordered_eges.end(), compare_edges);     //First sort the edges by weight
    std::vector<KruskalVertex> vertices;
    std::vector<edge> mst;

    for(unsigned int i=0; i<=n; ++i){
        vertices.push_back(KruskalVertex(i));           //initialize vertices with label
    }

    for(edge e: ordered_eges){       //Let e = (x,y) be the edge from x->y. We want to find out whether we should add e
        unsigned int a = vertices[std::get<0>(e)].get_root_label();     //Find representative of first x
        unsigned int b = vertices[std::get<1>(e)].get_root_label();     //Find representative of second y
        if(a!=b){           //If they are not the same, adding e will not create a cycle -> do it
            mst.push_back(e);           //We add the edge
            vertices[a].merge(vertices[b]);    //Now x and y are in the same connected component -> merge trees
            std::cout<<"Merging: ";
        }

        std::cout<<a<<" "<<b<<std::endl;
    }

    return mst;
}

int main(){
    std::vector<edge> graph({edge(0, 1, 3), edge(1,2,4), edge(1,3,10), edge(3,4,12),
                             edge(4,2,2), edge(4,5,8), edge(0,5,6), edge(5,6,7),
                             edge(2,6,5)});

    std::vector<edge> result = kruskal(graph, 6);
    std::cout<<std::endl;
    for(edge e: result){
        std::cout<<std::get<0>(e)<<" "<<std::get<1>(e)<<std::endl;
    }
    return 0;
}
#include "FibonacciHeap.h"
#include <iostream>
#include <vector>
#include <limits>


struct Node{
    bool explored;
    bool is_frontier;
    double distance_to_start;
    unsigned int prev;
    std::vector<std::pair<unsigned int, double>> adjacencies;
};

struct Edge{
    unsigned int node_a;
    unsigned int node_b;
    double length;
};

std::vector<unsigned int> dijkstra(std::vector<Edge> edges, unsigned int start, unsigned int stop, unsigned int graph_size){
    std::vector<Node> graph(graph_size, {false, false, std::numeric_limits<double>::infinity(), 0, {}});
    std::vector<FibonacciHeap<unsigned int>::handle_type> handles(graph_size, nullptr);
    FibonacciHeap<unsigned int> frontier;

    for(Edge current_edge: edges){
        graph[current_edge.node_a].adjacencies.emplace_back(current_edge.node_b, current_edge.length);
        graph[current_edge.node_b].adjacencies.emplace_back(current_edge.node_a, current_edge.length);
    }

    graph[start].distance_to_start = 0;
    graph[start].explored = true;

    for(std::pair<unsigned int, double> neighbour: graph[start].adjacencies){
        handles[neighbour.first] = frontier.push(neighbour.first, neighbour.second);
        graph[neighbour.first].is_frontier = true;
        graph[neighbour.first].distance_to_start = neighbour.second;
        graph[neighbour.first].prev = start;
    }

    unsigned int newly_explored;

    while(true){
        double newly_explored_distance  = frontier.min_key();
        newly_explored = frontier.extract_min();
        graph[newly_explored].is_frontier = false;
        graph[newly_explored].explored = true;

        if(newly_explored == stop){
            break;
        }

        for(std::pair<unsigned int, double> neighbour: graph[newly_explored].adjacencies){
            Node& neighbour_node = graph[neighbour.first];

            if(!neighbour_node.is_frontier && !neighbour_node.explored){
                neighbour_node.is_frontier = true;
                handles[neighbour.first] = frontier.push(neighbour.first, newly_explored_distance+neighbour.second);
                neighbour_node.distance_to_start = newly_explored_distance+neighbour.second;
                neighbour_node.prev = newly_explored;
            }

            else if(!neighbour_node.explored && neighbour_node.distance_to_start>newly_explored_distance+neighbour.second) {
                neighbour_node.distance_to_start=newly_explored_distance + neighbour.second;
                frontier.decrease_key(handles[neighbour.first], newly_explored_distance + neighbour.second);
                neighbour_node.prev = newly_explored;
            }
        }
    }

    std::vector<unsigned int> path;
    unsigned int current_node = newly_explored;

    while(current_node!=start){
        path.insert(path.begin(), current_node);
        current_node = graph[current_node].prev;
    }

    path.insert(path.begin(), start);
    return path;
}


int main(){
    std::vector<Edge> my_edges = {{0,8,1},{0,4,1}, {2,1,3}, {8,1,100}, {8,2,2}, {2,3,10}, {3, 7, 25}, {0,4,1}, {3,6,2},
                                          {6,5,100}, {1,5,2}, {2,4,1}};
    for(unsigned int node: dijkstra(my_edges, 0, 7, 9)){
        std::cout<<node<<" ";
    }
    return 0;
}
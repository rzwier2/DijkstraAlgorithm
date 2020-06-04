#include "graph.hpp"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Constructor. Know the graph size in advance
WeightedGraph::WeightedGraph(int num_nodes_) {
    num_nodes = num_nodes_;
    edge_counter = 0;
    data = new double[num_nodes * num_nodes];
    for (int i = 0; i < num_nodes; ++i) {
            data[i] = 0;
        }
}

// Destructor
WeightedGraph::~WeightedGraph() {
        delete[] data;
}

// Add a new edge to the graph
// If it exists already, update the weight.
void WeightedGraph::addEdge(int u, int v, double w) {
    if (getWeight(u, v) == 0) 
        ++edge_counter;  
    data[index(u, v)] = w;
    data[index(v, u)] = w;
}

// Get the number of nodes in the graph
int WeightedGraph::numNodes() const {
    return num_nodes;
}

// Get the number of edges in the graph
int WeightedGraph::numEdges() const {
    return edge_counter; 
}

// Return a list of neighbors for a given vertex
vector<int> WeightedGraph::neighbors(int u) {
    vector<int> nextto;
    for (int i = 0; i < num_nodes; ++i) {
        if (areConnected(u, i)) {
            nextto.push_back(i); 
        } 
    }
    return nextto;
}


// Check if two nodes are connected
bool WeightedGraph::areConnected(int u, int v) {
    return getWeight(u, v) != 0;  
}

// Get the weight of the edge between two nodes
// If there is no edge, return 0.
double WeightedGraph::getWeight(int u, int v) {
    return data[index(u, v)];
}

// Print out the graph's adjacency matrix
void WeightedGraph::print() {
    cout << "Graph with " << num_nodes << " nodes and " << edge_counter << " edges." << endl;
    for (int i = 0; i < num_nodes; ++i) {
        for (int j = 0; j < num_nodes; ++j) {
            cout << getWeight(i, j) << "\t";
        }     
    cout << endl; 
    }   
}


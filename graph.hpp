#ifndef __GRAPH_HPP
#define __GRAPH_HPP

#include <vector>

class WeightedGraph {
public:
    WeightedGraph(int num_nodes);
    ~WeightedGraph();

    void addEdge(int u, int v, double w);
    int numNodes() const;
    int numEdges() const;

    std::vector<int> neighbors(int u);
    bool areConnected(int u, int v);
    double getWeight(int u, int v);

    void print();

private:
    int num_nodes;
    int edge_counter;
    double * data;
    int index(int row, int col) { return row * num_nodes + col; } 

};

#endif

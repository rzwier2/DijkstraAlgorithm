#include <iostream>
#include <fstream>
#include <string>
#include "graph.hpp"
using namespace std;

vector<int> shortestPath(WeightedGraph& G, int source, int destination);

int main(int argc, char * argv[]) {
    fstream fin(argv[1]);
    
    // Read the header of the file: Number of nodes
    string token;
    int num_nodes;
    fin >> num_nodes >> token; // Reads in
    cout << "Reading a graph with " << num_nodes << " nodes." << endl; 

    // Read the header file: From where to where?
    int source, dest;
    fin >> token >> token >> source >> token >> dest;
    cout << "Goal: go from " << source << " to " << dest << endl;

    // Now that we know the size, create a new graph
    WeightedGraph G(num_nodes); 
   
    // Read the body of the problem file
    int u, v;
    double w;
    while (fin >> u >> v >> w) {
         G.addEdge(u, v, w);
    }      

    fin.close();
 
    // Function call
    shortestPath(G, source, dest);
}


// FUNCTION IMPLEMENTATION
vector<int> shortestPath(WeightedGraph& G, int source, int destination) {
    
    // Get the number of nodes from WeightedGraph
    int N = G.numNodes();     

    // Create array of doubles and fill it with the value -1
    // Will hold the shortest distance possible to each node
    double * shortest_distance;
    shortest_distance = new double[N];
    for (int i = 0; i < N; ++i) {
        shortest_distance[i] = -1;
    }    

    // Create array of ints and fill it with the value -1
    // Will store how to get to this node
    int * predecessor;
    predecessor = new int[N];
    for (int j = 0; j < N; ++j) {
        predecessor[j] = -1;
    }

    int u_min, v_min = -1;
    vector<int> path;

    shortest_distance[source] = 0;
    
    // Enter the main loop:
    while (v_min != destination) {
        double temp = 100000000;
        for (int i = 0; i < N; ++i) {
            if (shortest_distance[i] >= 0) {
                vector<int> nbrs = G.neighbors(i);
                for (int j = 0; j < nbrs.size(); ++j) {
                    int v = nbrs[j];
                    if (shortest_distance[v] == -1) {
                        double w_uv = G.getWeight(i, v);
                        if (w_uv + shortest_distance[i] < temp) {   
                            temp = w_uv + shortest_distance[i];
                            u_min = i;
                            v_min = v;
                        }
                    }    
                } // inside for loop
            }                 
        } // outer for loop

        // Return an empty vector if there is no possible 
        // path from source to destination
        if (temp == 100000000) {
        return path;
        }
   
        // Uodate the two arrays
        shortest_distance[v_min] = temp; // shortest_distance[u_min] + w_uv;
        predecessor[v_min] = u_min;
    
    } // while

    int tempNum = destination;            
    while (tempNum != source) {
        path.push_back(tempNum);
        tempNum = predecessor[tempNum];
    }
    path.push_back(source);

    // cout the shortest path    
    cout << "Shortest Path:" << endl;
    for (int i = path.size() - 1; i >= 0; --i) {
        cout << path.at(i) << endl;
    }

    return path;
}


/* ||||||||||||| SOURCES ||||||||||||||
 https://stackoverflow.com/questions/3904224/declaring-a-pointer-to-multidimensional-array-and-allocating-the-array
 http://www.cplusplus.com/reference/string/stod/
 http://www.cplusplus.com/reference/string/stoi/ 
 http://www.geeksforgeeks.org/c-classes-and-objects/
 http://www.cplusplus.com/doc/tutorial/functions/
 http://www.cplusplus.com/doc/tutorial/pointers/
 Worked with Dr. Wilson in office hours
 Worked with Caroline in Quantitative Skills Center Drop in hours
*/

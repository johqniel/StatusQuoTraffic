//
//  graph_import_export.cpp
//  BridgeModel
//
//  Created by nielo on 12.05.25.
//

#include "graph.h"
#include <fstream>
#include "iostream"



Graph create_test_graph(){
    Graph test_graph;
    test_graph.addEdge(0,1,0,"None");
    test_graph.addEdge(0,2,1,"None");
    test_graph.addEdge(1,3,2,"None");
    test_graph.addEdge(2,3,0,"None");
    test_graph.addEdge(3,4,0,"None");
    test_graph.addEdge(3,5,1,"None");
    test_graph.addEdge(4,6,2,"None");
    test_graph.addEdge(5,6,0,"None");
    //test_graph.addEdge(7,7,1);
    test_graph.size_of_subgraphs = 7;
    return(test_graph);
}

Graph create_test_graph_large() {
    // Start with 15 nodes.
    Graph graph;

    // home verticies: 0,15,16,17
    // work verticy: 14
    
    // number of verts: 18
    
//# Diagram mapping to coordinates:
//# -------------------------
//# |   | 1 | 4 | 7 | 11|   |  (Y=1)
//# -------------------------
//# | 0 | 17| 16| 8 | 12| 14|  (Y=0)
//# -------------------------
//# |   | 2 | 5 | 9 | 13|   |  (Y=-1)
//# -------------------------
//# |   | 15| 3 | 6 | 10|   |  (Y=-2)
//# -------------------------
    
    // Create several paths from node 0 to node 14, with intersections.
    
    
    graph.addEdge(0, 1, 0,"None");
    graph.addEdge(0, 2, 1,"None");
    graph.addEdge(0, 3, 2,"None");

    graph.addEdge(1, 4, 0,"None");
    graph.addEdge(2, 4, 1,"None");
    graph.addEdge(2, 5, 0,"None");
    graph.addEdge(3, 5, 1,"None");
    graph.addEdge(3, 6, 2,"None");

    graph.addEdge(4, 7, 0,"None");
    graph.addEdge(4, 8, 1,"None");
    graph.addEdge(5, 8, 2,"None");
    graph.addEdge(5, 9, 0,"None");
    graph.addEdge(6, 9, 1,"None");
    graph.addEdge(6, 10, 2,"None");

    graph.addEdge(7, 11, 0,"None");
    graph.addEdge(8, 11, 1,"None");
    graph.addEdge(8, 12, 0,"None");
    graph.addEdge(9, 12, 1,"None");
    graph.addEdge(9, 13, 2,"None");
    graph.addEdge(10, 13, 0,"None");

    graph.addEdge(11, 14, 0,"None");
    graph.addEdge(12, 14, 1,"None");
    graph.addEdge(13, 14, 2,"None");
    
    graph.addEdge(15, 5, 1,"None");
    graph.addEdge(15, 3, 2,"None");
    
    graph.addEdge(16, 8, 2,"None");
    graph.addEdge(16, 5, 1,"None");
    
    graph.addEdge(17, 1, 2,"None");
    graph.addEdge(17, 5, 1,"None");




    graph.size_of_subgraphs = 18;
    graph.homeOptions = {0,15,16,17};
    graph.workOptions = {14};
    return graph;
}

Graph create_test_graph_large_old() {
    // Start with 15 nodes.
    Graph graph;

    // Create several paths from node 0 to node 14, with intersections.
    graph.addEdge(0, 1, 0,"None");
    graph.addEdge(0, 2, 1,"None");
    graph.addEdge(0, 3, 2,"None");

    graph.addEdge(1, 4, 0,"None");
    graph.addEdge(2, 4, 1,"None");
    graph.addEdge(2, 5, 0,"None");
    graph.addEdge(3, 5, 1,"None");
    graph.addEdge(3, 6, 2,"None");

    graph.addEdge(4, 7, 0,"None");
    graph.addEdge(4, 8, 1,"None");
    graph.addEdge(5, 8, 2,"None");
    graph.addEdge(5, 9, 0,"None");
    graph.addEdge(6, 9, 1,"None");
    graph.addEdge(6, 10, 2,"None");

    graph.addEdge(7, 11, 0,"None");
    graph.addEdge(8, 11, 1,"None");
    graph.addEdge(8, 12, 0,"None");
    graph.addEdge(9, 12, 1,"None");
    graph.addEdge(9, 13, 2,"None");
    graph.addEdge(10, 13, 0,"None");

    graph.addEdge(11, 14, 0,"None");
    graph.addEdge(12, 14, 1,"None");
    graph.addEdge(13, 14, 2,"None");

    graph.size_of_subgraphs = 15;
    return graph;
}

// Function to export graph to file to then read it with python and plot it.
void Graph::exportToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file for writing: " << filename << std::endl;
        return;
    }

    for (const auto& [u, edges] : adjList) {
        
        
        for (const auto& [v,info] : edges) {
            double weight = std::get<0>(info);
            std::string type = std::get<1>(info);
            int flow = std::get<3>(info);
            // entry 3 is flow_old which is equal to flow after each simulated period.
            int capacity = std::get<4>(info);
            
            
            file << u << " " << v << " " << weight << " " << type << " " << flow << " " << capacity << "\n";
        }
    }

    file.close();
    std::cout << "Graph exported to " << filename << std::endl;
}

void Graph::removeEmptyTypeEdges() {
    // We'll collect the edges to remove first to avoid modifying the map
    // while iterating over it, which can invalidate iterators.
    // Stores pairs of (u, v) for edges to be removed.
    std::vector<std::pair<int, int>> edges_to_remove;

    // Iterate through all source nodes (u) in the adjacency list
    for (const auto& u_pair : adjList) {
        int u = u_pair.first; // The current source node ID

        // Iterate through all destination nodes (v) and their edge data
        // from the current source node u.
        for (const auto& v_pair : u_pair.second) {
            int v = v_pair.first; // The current destination node ID
            const auto& edge_data = v_pair.second; // The tuple containing edge properties

            // Get the 'type' string from the tuple (it's the second element, index 1)
            std::string type = std::get<1>(edge_data);

            // Check if the type string is empty
            if (type.empty()) {
                // If it's empty, mark this edge (u, v) for removal.
                // We add it to our temporary list.
                edges_to_remove.push_back({u, v});
            }
        }
    }

    // Now, iterate through the collected edges and remove them from the adjList.
    // We do this in a separate loop to safely modify the map.
    for (const auto& edge : edges_to_remove) {
        int u = edge.first;  // Source node of the edge to remove
        int v = edge.second; // Destination node of the edge to remove

        // Remove the edge (u, v)
        // We check if 'u' exists in the outer map and 'v' in the inner map
        // before attempting to erase, for robustness.
        if (adjList.count(u) && adjList[u].count(v)) {
            adjList[u].erase(v);
            // Optional: If the inner map for 'u' becomes empty after removal,
            // you might want to remove 'u' from the outer adjList to keep it clean.
            // if (adjList[u].empty()) {
            //     adjList.erase(u);
            // }
        }

        // Assuming your graph is undirected (edges are added symmetrically),
        // we also need to remove the corresponding (v, u) edge.
        if (adjList.count(v) && adjList[v].count(u)) {
            adjList[v].erase(u);
            // Optional: Same as above, if adjList[v] becomes empty.
            // if (adjList[v].empty()) {
            //     adjList.erase(v);
            // }
        }
    }
}

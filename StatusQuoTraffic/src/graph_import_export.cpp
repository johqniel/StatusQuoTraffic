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
    test_graph.addEdge(0,1,0);
    test_graph.addEdge(0,2,1);
    test_graph.addEdge(1,3,2);
    test_graph.addEdge(2,3,0);
    test_graph.addEdge(3,4,0);
    test_graph.addEdge(3,5,1);
    test_graph.addEdge(4,6,2);
    test_graph.addEdge(5,6,0);
    //test_graph.addEdge(7,7,1);
    test_graph.size_of_subgraphs = 7;
    return(test_graph);
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

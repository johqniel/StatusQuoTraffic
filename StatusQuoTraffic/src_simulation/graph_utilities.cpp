//
//  graph_utilities.cpp
//  BridgeModel
//
//  Created by nielo on 12.05.25.
//

#include "graph.h"
#include <iostream>
#include <unordered_set>



std::string Graph::determine_comuter_type(std::vector<int> path){
    // gets a path and determines what kind of commuter type this is.
    // the path begins in the end of the vector.
    
    if (path.size() < 4){
        throw std::runtime_error("Tried to find out the comuter type of a path of length < 4");
    }
    std::string type_enter = std::get<1>(adjList[path.size() - 2][path.size() - 3]);
    /*
    if (type_enter == "bike-public"){
        if
    }
    if (type_enter ==  "public-bike"){
        
    }
    if(type_enter == "car-public"){
        
    }
     for now we dont need this detail */
    
    return type_enter;
};

void Graph::update_flow_on_paths(std::vector<int> old_path, std::vector<int> new_path){
    //std::cout << "flow is updated" << std::endl;
    if (old_path.size() == 0){
        // increase flow by one on new path
        if (new_path.size() == 0){
            std::cerr << "new path is also empty" << std::endl;
        }
        for (int i = new_path.size() - 3; i  > 0; i --){
            increaseNewFlowFAST(new_path[i], new_path[i-1]);
        }
        return;
    }
    if (new_path.size() == 0){
        std::cerr << "new path is empty" << std::endl;
    }
    if (old_path[0] != new_path[0]){
        std::cerr << "Beginning of paths in update_weights_on_paths not equal" << std::endl;
    }
    if (old_path.back() != new_path.back()){
        std::cerr << "Ending of paths in update_weights_on_paths not equal" << std::endl;
    }
    if (old_path[0] > size_of_subgraphs ||
        old_path.back() > size_of_subgraphs ||
        new_path[0] > size_of_subgraphs ||
        new_path.back() > size_of_subgraphs){
        std::cerr << "Beginning / Ending not on designated subgraph." << std::endl;
    }
    
    // reduce flow by one on old path (we have to run backwards through the array because thats how dijkstra returns the path
    for (int i = old_path.size() - 3; i  > 0; i --){
        decreaseNewFlowFAST(old_path[i], old_path[i-1]);
    }
    // increase flow by one on new path
    for (int i = new_path.size() - 3; i  > 0; i --){
        increaseNewFlowFAST(new_path[i], new_path[i-1]);
    }
}

void Graph::update_flow_all_edges(){
    for (auto& [u, neighbors] : adjList) {
        for (auto& [v, edge] : neighbors) {
            // Set old flow (3rd element) equal to new flow (4th element)
            std::get<2>(edge) = std::get<3>(edge);
        }
    }
    
}


unsigned long Graph::countALLVerts() const {
    std::unordered_set<int> uniqueNodes;

    // Add all source nodes
    for (const auto& [u, edges] : adjList) {
        uniqueNodes.insert(u);
        
        // Add all target nodes
        for (const auto& [v, _] : edges) {
            uniqueNodes.insert(v);
        }
    }
    return uniqueNodes.size();
}


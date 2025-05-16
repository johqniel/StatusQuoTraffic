//
//  graph_build.cpp
//  BridgeModel
//
//  Created by nielo on 12.05.25.
//

#include "graph.h"
#include "agent.h"
#include "utilities.h"
#include "iostream"







void Graph::expandGraphForTransportTypes() {
    // Step 2: Define which types to add
    std::vector<std::string> extra_types = subgraph_types;
                                        // {"bike","public", "car", "bike-public", "public-bike", "car-public"}
    
    
    // Step 3: Copy graph for each new type
    if (!(size_of_subgraphs == size())){
        std::cout << "Size of subgraphs (var): " << size_of_subgraphs << " is not equal to size of subgraph (function): " << size() << " as expected" << std::endl;
    
    }  // just to make sure

    
    // loop over types
        // loop over vertizies u < size_of_subgraph and add all verticies
    for (size_t i = 0; i < extra_types.size(); ++i) {
        std::string type = extra_types[i];
        int offset = (i + 1) * size_of_subgraphs;  // avoid overlap
        
        for (int u = 0; u < size_of_subgraphs; u++){
            const auto& edges = adjList[u];
            for (const auto& [v,info] : edges){
                double w = std::get<0>(info);
                // Add edge with offset and new type
                addEdge(u + offset, v + offset, w, type);
            }
            
        }
    }
    
    number_of_subgraphs = extra_types.size();  // original + copies
    
    // Step 4: delete original subgraph
    for (int u = 0; u < size_of_subgraphs; u ++) {
        adjList.erase(u);
    }
        
    // reinitilize orignal subgraph as exit points to the transportation network
    for (int u = 0; u < size_of_subgraphs; u ++){
        for(int i = 0; i < number_of_subgraphs; i ++){
            int offset = (i + 1) * size_of_subgraphs;
            //addEdge(u, u + offset, 0 , "walk"); // we used to have it as entry and exit points.
            addEdge(u + offset, u, 0, "walk");
        }
    }
    
    // add edges from bike-train graph to public graph,
    // add edges from public-bike graph to bike graph,
    // add edges from car-public graph to train graph,
    std::vector<std::string> special_types = {"bike-public", "public-bike", "car-public"};
    int subgraph_target[3] = {2,1,2};    // this part is hardcoded i dont like that
    int subgraph_origin[3] = {4,5,6};
    
    for (int u = 0; u < size_of_subgraphs; u ++){
        for(int i = 4; i < number_of_subgraphs + 1; i ++){
            int offset_from = (i) * size_of_subgraphs;
            int offset_to = subgraph_target[i-4] * size_of_subgraphs;
            addEdge(u + offset_from, u + offset_to, 0 , "walk");
        }
    }
    
    
}


void Graph::expandGraphForAgents(std::vector <Agent> agents){
    //std::vector<std::string> extra_types = subgraph_types;
        // "bike","public", "car", "bike-public", "public-bike", "car-public"
    
    
    int i = 1;
    for (std::string transportation_type : subgraph_types){
        int entry_vert_offset = i * size_of_subgraphs;
        std::cout << "size of subgraphs = " << size_of_subgraphs << std::endl;
        for (Agent agent : agents){
            addEdge(agent.agent_id,agent.home + entry_vert_offset, 0, "walk");
        }
            
        i += 1;
    }
    
}

void Graph::expandGraphForAgentsRandom(std::vector <Agent> agents){

    int i = 1;
    for (std::string transportation_type : subgraph_types){
        int entry_vert_offset = i * size_of_subgraphs;
        std::cout << "size of subgraphs = " << size_of_subgraphs << std::endl;
        for (Agent agent : agents){
            double random_weight = generate_random_double(0,12);
            addEdge(agent.agent_id,agent.home + entry_vert_offset, random_weight, "walk");
            std::cout << random_weight << std::endl;
        }
            
        i += 1;
    }
    
}

void Graph::update_entry_weights_according_to_commuter_type_matrix(std::vector<Agent> agents){

    for (Agent agent : agents){
        if (subgraph_types_set.find(agent.comuter_type) != subgraph_types_set.end()) {
            std::cout << "commuter type is not valid" << std::endl;
        }
        std::vector<double> personal_entry_weights = agent.entry_weights[agent.comuter_type];
        int i = 1;

        for (int entry_weight : personal_entry_weights){
            //std::cout << " we get here " << std::endl;
            std::get<0>(agent.map_ptr->adjList[agent.agent_id][agent.home + agent.map_ptr->size_of_subgraphs * i]) = entry_weight;
            i += 1;
        }
    }
};

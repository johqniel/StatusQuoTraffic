//
//  agent.cpp
//  BridgeModel
//
//  Created by nielo on 03.05.25.
//

#include "agent.h"
#include "graph.h"
#include "utilities.h"
#include <iostream>
#include <random>
#include <ctime>

void Agent::update_comuter_type(){
    std::string new_comuter_type = " none";
    if (path_new != path_old){
        new_comuter_type = map_ptr->determine_comuter_type(path_new);
        if (new_comuter_type == "none"){
            std::cerr << "new comuter type is none .... " << std::endl;
        }
        else if (new_comuter_type != comuter_type){
            comuter_type = new_comuter_type;
            update_personal_edges(new_comuter_type);
        }
    }
}


    

void Agent::update_flow(){
    if (path_new != path_old){
        //print_int_vector(path_old, "            enter update_flow: path old: ");
        //print_int_vector(path_new, "            path new: ");
        map_ptr->update_flow_on_paths(path_old, path_new);
        //std::cout << "          path old now equal to path new" << std::endl;
        path_old = path_new;
        
        //print_int_vector(path_old_, "            exit update_flow: path_old");
        //print_int_vector(path_new, "            path_new");

    }
}

/*
void Agent::setup_variables_for_next_period(){
    path_old = path_new;
}

*/
 
void Agent::best_path_to_work(){
    //print_int_vector(path_new, "before dijkstra new path: ");
    path_new = map_ptr->dijkstra_flow(agent_id,work);
}

std::vector<int> Agent::return_best_path_to_work(){
    return map_ptr->dijkstra(agent_id,work);
}

void Agent::update_personal_edges(std::string new_comuter_type){
    if(new_comuter_type == "bike"){
        
    }
    if(new_comuter_type == "public"){
        
    }
    if(new_comuter_type == "car"){
        
    }
    if(new_comuter_type == "bike-public"){
        
    }
    if(new_comuter_type == "public-bike"){
        
    }
    if(new_comuter_type == "car-public"){
        
    }
    if (map_ptr->subgraph_types_set.find(comuter_type) != map_ptr->subgraph_types_set.end()) {
        std::cout << "commuter type is not valid" << std::endl;
    }
    std::vector<double> personal_entry_weights = entry_weights[new_comuter_type];
    int i = 1;
    for (int entry_weight : personal_entry_weights){
        int v = agent_id;
        int u = home + map_ptr->size_of_subgraphs * i;
     
        map_ptr->changeEdgeWeightFAST(v, u, entry_weight);
        i += 1;
    }
}

void Agent::generate_profile(int agent_id, Graph* the_map){
    home = 0;
    work = 14;
    comuter_type = "bike";
    map_ptr = the_map;
    
}


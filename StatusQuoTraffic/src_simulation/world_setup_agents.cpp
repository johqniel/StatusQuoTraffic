//
//  world_setup.cpp
//  BridgeModel
//
//  Created by nielo on 15.05.25.
//

#include "world.h"
#include "utilities.h"
#include <iostream>


void World::add_agent(int agent_id){
    Agent new_agent;
    new_agent.agent_id = agent_id; // the new agents id is the number of its personal home verticy
    new_agent.generate_profile(agent_id, &map);
    agents.push_back(new_agent);
    // For each agent we have to add edges from their personal verticy (= their agent_id) to the home verticies of the subgraphs.
    // this is done in the build graph module for all agents at once
}


void World::initilize_agents(){
    for (int i = 0; i < number_of_agents; i++){
        add_agent(get_new_agent_id());
    }
}


void World::setup_commuter_types_weights_of_agents(){
    double min, max;
    for (auto& agent : agents){
        for (std::string commuter_type : map.subgraph_types){
            for (std::string desired_path_type : map.subgraph_types){
                min = std::get<0>(commuter_type_weights_matrix[commuter_type][desired_path_type]);
                max = std::get<1>(commuter_type_weights_matrix[commuter_type][desired_path_type]);
                agent.entry_weights[commuter_type].push_back(generate_random_double(min,max));
            }
        }
    }
}

void World::assign_random_initial_commuter_type_agents(){
    for (auto& agent : agents){
        std::string new_commuter_type = map.subgraph_types[generate_random_unsigned(map.subgraph_types.size()-1)];
        agent.comuter_type = new_commuter_type;
    }
};



void World::setup_commuter_type_weights_matrix(){
    for (std::string active_type : map.subgraph_types){
        for (std::string desired_path_type : map.subgraph_types){
            if (active_type == "bike"){
                if (desired_path_type == "bike-public" || desired_path_type == "bike"){
                    commuter_type_weights_matrix[active_type][desired_path_type] = {0,0};
                }
                else if (desired_path_type == "public-bike" || desired_path_type == "public"){
                    commuter_type_weights_matrix[active_type][desired_path_type] = {1,2};
                }
                else if (desired_path_type == "car" || desired_path_type == "car-public"){
                    commuter_type_weights_matrix[active_type][desired_path_type] = {1,8};
                }
                else {
                    std::cout << "Setup commuter type weights matrix was not set up as intended." << std::endl;
                    commuter_type_weights_matrix[active_type][desired_path_type] = {0,0};

                }
            }
            if (active_type == "public"){
                if (desired_path_type == "bike-public" || desired_path_type == "bike"){
                    commuter_type_weights_matrix[active_type][desired_path_type] = {1,2};
                }
                else if (desired_path_type == "public-bike" || desired_path_type == "public"){
                    commuter_type_weights_matrix[active_type][desired_path_type] = {0,0};
                }
                else if (desired_path_type == "car" || desired_path_type == "car-public"){
                    commuter_type_weights_matrix[active_type][desired_path_type] = {1,6};
                }
                else {
                    std::cout << "Setup commuter type weights matrix was not set up as intended." << std::endl;
                    commuter_type_weights_matrix[active_type][desired_path_type] = {0,0};

                }
            }
            if (active_type == "car"){
                if (desired_path_type == "bike-public" || desired_path_type == "bike"){
                    commuter_type_weights_matrix[active_type][desired_path_type] = {1,5};
                }
                else if (desired_path_type == "public-bike" || desired_path_type == "public"){
                    commuter_type_weights_matrix[active_type][desired_path_type] = {1,5};
                }
                else if (desired_path_type == "car" || desired_path_type == "car-public"){
                    commuter_type_weights_matrix[active_type][desired_path_type] = {0,0};
                }
                else {
                    std::cout << "Setup commuter type weights matrix was not set up as intended." << std::endl;
                    commuter_type_weights_matrix[active_type][desired_path_type] = {0,0};

                }
            }
            if (active_type == "bike-public" ){
                if (desired_path_type == "bike-public" || desired_path_type == "bike"){
                    commuter_type_weights_matrix[active_type][desired_path_type] = {1,5};
                }
                else if (desired_path_type == "public-bike" || desired_path_type == "public"){
                    commuter_type_weights_matrix[active_type][desired_path_type] = {1,5};
                }
                else if (desired_path_type == "car" || desired_path_type == "car-public"){
                    commuter_type_weights_matrix[active_type][desired_path_type] = {0,0};
                }
                else {
                    std::cout << "Setup commuter type weights matrix was not set up as intended." << std::endl;
                    commuter_type_weights_matrix[active_type][desired_path_type] = {0,0};

                }
            }
            if (active_type == "public-bike"){
                if (desired_path_type == "bike-public" || desired_path_type == "bike"){
                    commuter_type_weights_matrix[active_type][desired_path_type] = {0,0};
                }
                else if (desired_path_type == "public-bike" || desired_path_type == "public"){
                    commuter_type_weights_matrix[active_type][desired_path_type] = {0,0};
                }
                else if (desired_path_type == "car" || desired_path_type == "car-public"){
                    commuter_type_weights_matrix[active_type][desired_path_type] = {1,6};
                }
                else {
                    std::cout << "Setup commuter type weights matrix was not set up as intended." << std::endl;
                    commuter_type_weights_matrix[active_type][desired_path_type] = {0,0};

                }
            }
            if (active_type == "car-public"){
                if (desired_path_type == "bike-public" || desired_path_type == "bike"){
                    commuter_type_weights_matrix[active_type][desired_path_type] = {1,8};
                }
                else if (desired_path_type == "public-bike"){
                    commuter_type_weights_matrix[active_type][desired_path_type] = {1,8};
                }
                else if (desired_path_type == "public"){
                    commuter_type_weights_matrix[active_type][desired_path_type] = {0,0};
                }
                else if (desired_path_type == "car" || desired_path_type == "car-public"){
                    commuter_type_weights_matrix[active_type][desired_path_type] = {0,0};
                }
                else {
                    std::cout << "Setup commuter type weights matrix was not set up as intended." << std::endl;
                    commuter_type_weights_matrix[active_type][desired_path_type] = {0,0};

                }
            }
        }
    }
}


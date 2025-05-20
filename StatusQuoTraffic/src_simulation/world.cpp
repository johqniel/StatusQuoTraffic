//
//  world.cpp
//  BridgeModel
//
//  Created by nielo on 03.05.25.
//

#include "world.h"
#include "utilities.h"
#include <vector>
#include <queue>
#include <iostream>



void World::start_simulation(){
    for (int t = 0; t < simulation_horizon; t++){
        //std::cout << "Simulating time step t = " << t << std::endl;
        //std::cout << "Agent number 1 id: " << agents[0].agent_id <<  " and path: " <<"";
        print_int_vector(agents[0].path_old);
        std::cout << std::endl;
        
        update();
        
        std::cout << "Simulated time step t = " << t << std::endl;
        int random_id = generate_random_unsigned(number_of_agents);
        std::cout << "Agent number " << random_id << " : " << agents[random_id].agent_id << " and path: " << "";
        print_int_vector(agents[random_id].path_old);
        
        std::cout << std::endl;

    }
}

void World::start_simulation_write_data(){
    for (int t = 0; t < simulation_horizon; t++){
        //std::cout << "Simulating time step t = " << t << std::endl;
        //std::cout << "Agent number 1 id: " << agents[0].agent_id <<  " and path: " <<"";
        print_int_vector(agents[0].path_old);
        std::cout << std::endl;
        
        update();
        
        std::cout << "Simulated time step t = " << t << std::endl;
        int random_id = generate_random_unsigned(number_of_agents);
        std::cout << "Agent number " << random_id << " : " << agents[random_id].agent_id << " and path: " << "";
        print_int_vector(agents[random_id].path_old);
        
        std::cout << std::endl;
        std::string file_name = "graph_" + std::to_string(t) + ".txt";
        map.exportToFile("/Users/nielo/Desktop/StatusQuoTraffic/StatusQuoTraffic/data/" + file_name);
    }
}

void World::setup_simulation(){
    setup_commuter_type_weights_matrix();
    initilize_map();
    nextFreeAgentId = map.countALLVerts() + 1; // the plus one is there just to make sure :-D
    initilize_agents();
    setup_commuter_types_weights_of_agents();
    build_map();
    assign_random_initial_commuter_type_agents();

    //add_randomness_to_agents();
}





unsigned long World::get_new_agent_id(){
    unsigned long new_id = nextFreeAgentId;
    nextFreeAgentId += 1;
    return new_id;
}

/*

void World::add_randomness_to_agents(){
    for (auto& agent : agents){
        agent.add_randomness_to_agents_test(number_of_subgraphs);
    }
}

*/

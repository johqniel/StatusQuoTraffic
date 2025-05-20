//
//  world_update.cpp
//  BridgeModel
//
//  Created by nielo on 15.05.25.
//

#include "world.h"


void World::update(){
    update_agents();
    update_graph();
    
}

void World::update_graph(){
    map.update_flow_all_edges();
}

void World::update_agents(){
    for (auto& agent : agents){
        //agent.path_plain = agent.return_best_path_to_work();
        //std::cout << "  Agent number: " << agent.agent_id << std::endl;
        //std::cout << "Agent path_plain after update: ";
        //        print_int_vector(agent.path_plain);
        //        std::cout << std::endl;
        //print_int_vector(agent.path_new, "  new_path outside");
        agent.best_path_to_work();
        //print_int_vector(agent.path_new, "  new_path outside after dijkstra");
        agent.update_flow();
        //agent.setup_variables_for_next_period(); // now done directly in update_flow
        agent.update_comuter_type();
    }
}

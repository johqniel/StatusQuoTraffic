//
//  world_setup_map.cpp
//  BridgeModel
//
//  Created by nielo on 15.05.25.
//

#include "world.h"

void World::initilize_map(){
    map = create_test_graph_large();
    map.expandGraphForTransportTypes();
}


void World::build_map(){
    map.expandGraphForAgentsRandom(agents);
}

void World::expand_graph_from_subgraph(const Graph& subgraph){
    map.expandGraphForTransportTypes();
}



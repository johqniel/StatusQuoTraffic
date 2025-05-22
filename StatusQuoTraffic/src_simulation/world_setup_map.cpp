//
//  world_setup_map.cpp
//  BridgeModel
//
//  Created by nielo on 15.05.25.
//

#include "world.h"

void World::initilize_map(graphIdentifier graphInfo){
    if (graphInfo.graph_identifier == "test_large_graph_three_entry"){
        map = create_test_graph_large();
        
    }
    else if (graphInfo.graph_identifier == "test_small_graph"){
        
    }
    else{
        std::cout << "unknown graph selected." << std::endl;
    }
    homeOptions = graphInfo.homeOptions;
    workOptions = graphInfo.workOptions;
    //typeOptions = graphInfo.typeOptions;
    map.expandGraphForTransportTypes();
}


void World::build_map(){
    map.expandGraphForAgentsRandom(agents);
}

void World::expand_graph_from_subgraph(const Graph& subgraph){
    map.expandGraphForTransportTypes();
}



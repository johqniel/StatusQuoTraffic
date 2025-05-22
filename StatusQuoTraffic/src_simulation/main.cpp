//
//  main.cpp
//  BridgeModel
//
//  Created by nielo on 21.04.25.
//

#include <iostream>
#include "graph.h"
#include "utilities.h"
#include "world.h"

int main(int argc, const char * argv[]) {
   
    Graph test_graph = create_test_graph_large();
    
    //test_graph.size_of_subgraphs = 7;
    print_int_vector(test_graph.dijkstra(0,14));

    
    
    test_graph.expandGraphForTransportTypes();
    
    std::cout << "The shortest path from 0 to 14 is: " << std::endl;
    print_int_vector(test_graph.dijkstra(15,14));
    test_graph.printNeighbors(15);
    
    std::cout << "Everything ran through" << std::endl;

    std::cout << "Size of subgraphs is: " << test_graph.size_of_subgraphs << std::endl;
    
    test_graph.printNeighbors(14);
    test_graph.exportToFile("/Users/nielo/Desktop/StatusQuoTraffic/StatusQuoTraffic/data/oke.txt");
    
    //test_graph.exportToFile("test_graph.txt");
    //test_graph.exportToFile("/Users/nielo/Desktop/BridgeModel/BridgeModel/BridgeModel/graph_map.txt");
    
    
    
    //test_world.initilize_map();
    worldSettings worldInfo;
    worldInfo.number_of_agents = 0;
    worldInfo.simulation_horizon = 10;
    worldInfo.graphIdentifier = "test_large_graph_three_entry";
    
    graphIdentifier graphInfo;
    
    // create world
    World test_world;
    test_world.number_of_agents = worldInfo.number_of_agents;
    test_world.simulation_horizon = worldInfo.simulation_horizon;
    
    // setup world
    test_world.setup_simulation(graphInfo);
    
    // export world
    test_world.map.exportToFile("/Users/nielo/Desktop/StatusQuoTraffic/StatusQuoTraffic/data/graph_test.txt");

    /*
    
    test_world.start_simulation_write_data();
    
    test_world.map.exportToFile("/Users/nielo/Desktop/StatusQuoTraffic/StatusQuoTraffic/data/graph_whole.txt");
    
    for (auto& agent : test_world.agents){
        //std::cout << std::get<0>(test_world.map.adjList[agent.agent_id][7]) << std::endl;
    }
    //std::cout << "Dijkstra from 7 to 13: " << size(test_world.map.dijkstra(7,13)) << std::endl;
    
    */
    
    return 0;
}

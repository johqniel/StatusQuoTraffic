//
//  main.cpp
//  BridgeModel
//
//  Created by nielo on 21.04.25.
//

#include <iostream>
#include "graph.h"
#include "test.h"
#include "utilities.h"
#include "world.h"

int main(int argc, const char * argv[]) {
   
    Graph test_graph = create_test_graph();
    
    test_graph.size_of_subgraphs = 7;
    
    test_graph.expandGraphForTransportTypes();
    
    std::cout << "The shortest path from 1 to 7 is: " << std::endl;
    print_int_vector(test_graph.dijkstra(0,6));
    
    std::cout << "Everything ran through" << std::endl;

    std::cout << "Size of subgraphs is: " << test_graph.size_of_subgraphs << std::endl;
    
    //test_graph.exportToFile("test_graph.txt");
    //test_graph.exportToFile("/Users/nielo/Desktop/BridgeModel/BridgeModel/BridgeModel/graph_map.txt");
    
    
    World test_world;
    //test_world.initilize_map();
    test_world.subgraph_size = 7;
    
    test_world.setup_simulation();
    test_world.start_simulation();
    
    test_world.map.exportToFile("/Users/nielo/Desktop/StatusQuoTraffic/graph_whole.txt");
    
    for (auto& agent : test_world.agents){
        //std::cout << std::get<0>(test_world.map.adjList[agent.agent_id][7]) << std::endl;
    }
    //std::cout << "Dijkstra from 7 to 13: " << size(test_world.map.dijkstra(7,13)) << std::endl;
    
    return 0;
}

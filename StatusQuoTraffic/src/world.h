//
//  world.h
//  BridgeModel
//
//  Created by nielo on 03.05.25.
//

#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <queue>
#include "graph.h"
#include "agent.h"
#include "utilities.h"
#include "test.h"

class World{
public:
    int subgraph_size;
    int number_of_subgraphs = 6;
    std::vector<Agent> agents;
    Graph map;
    int simulation_horizon = 10;
    int number_of_agents = 1000;
    unsigned long nextFreeAgentId = 0;
    std::unordered_map<std::string,std::unordered_map<std::string,std::tuple<double ,double >>> commuter_type_weights_matrix;
    // works as follows active_comuter_type -> desired_path_type -> min weight to entry that path
    //                                                           -> max weight to entry that path
    
    
    void setup_simulation(); // contains:
        void initilize_map();      // 1.
        void initilize_agents();   // 2.
        void build_map();          // 3.
    
    void start_simulation(); // contains
        // for loop t in 1,.. horizon
            // update()
    
    void setup_commuter_type_weights_matrix();
    void setup_commuter_types_weights_of_agents();
    void assign_random_initial_commuter_type_agents();
    //randomness
    
    //void add_randomness_to_agents();

    
private:
    void update(); // contains
        void update_agents(); // 1.
        void update_graph();  // 2.
        void save_data();     // not yet

    
    // Other functions
    
    void expand_graph_from_subgraph(const Graph& subgraph);
    void add_agent(int agent);
    unsigned long get_new_agent_id();

};



#endif // world.h


//
//  agent.h
//  BridgeModel
//
//  Created by nielo on 03.05.25.
//

#ifndef AGENT_H
#define AGENT_H

#include <vector>
#include <queue>

// Forward declaration of Graph
class Graph;

class Agent{
public:
    
    Graph* map_ptr;   // the map on which the whole simulation is happening
    
    int agent_id;
    int home;          // location where agent lives ( a verticy on the graph)
    int work;          // location where agent works ( a verticy on the graph)
    
    std::string comuter_type; // comuter types are: car, car-train, bike, bike-train, and train
                      // depending
    
    std::vector<int> path_old;
    std::vector<int> path_new;
    std::unordered_map<std::string,std::vector<double>> entry_weights;
    //std::vector<int> path_plain; for debugging
    
    
 // Functions
    
    // utilities
    
    void best_path_to_work();
    std::vector<int> return_best_path_to_work();
    
    // update functions
    void update_comuter_type();
    void update_flow();
    void update_personal_edges(std::string);

    // setup functions
    void setup_variables_for_next_period();
    void generate_profile(int agent_id, Graph* the_map);
    
    // randomnes
    
    //void add_randomness_to_agents_test(unsigned number_of_subgraphs);
    
private:
};

#endif // agent.h

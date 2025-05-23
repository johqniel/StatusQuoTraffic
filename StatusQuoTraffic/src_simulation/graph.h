//
//  graph.h
//  BridgeModel
//
//  Created by nielo on 21.04.25.
//

#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <queue>
#include <unordered_set>
#include "agent.h"


struct graphIdentifier{
    int size_of_subgraphs = 18;
    std::string graph_identifier = "test_large_graph_three_entry";
    std::vector<int> homeOptions = {0,15,16,17};
    std::vector<int> workOptions = {14};
};

class Graph {
public:
    // functions:
    
    void addEdge(int u, int v, double weight, std::string type = "none", int flow = 0, int flow_new = 0, int capacity = 20); // done
    
    // build Graph
    void expandGraphForTransportTypes();
    void expandGraphForAgents(std::vector<Agent> agents);
    void expandGraphForAgentsRandom(std::vector <Agent> agents);
    void update_entry_weights_according_to_commuter_type_matrix(std::vector<Agent> agents);
   
    
    // import export
    void exportToFile(const std::string& filename);
    void removeEmptyTypeEdges();
    
    // graph functions
    std::vector<int> dijkstra(int source, int target);
    //std::vector<int> dijkstra_flow(int source, int target);

    int size();
    
    // graph utilities
    void changeEdgeWeightFAST(int u, int v, double newWeight);
    bool changeEdgeWeightCHECK(int u, int v, double newWeight);
    void changeEdgeFlowFAST(int u, int v, int new_flow);
    bool changeEdgeFlowCHECK(int u, int v, int new_flow);
    void increaseNewFlowFAST(int u, int v);
    void decreaseNewFlowFAST(int u, int v);
    unsigned long countALLVerts() const;
    void printNeighbors(int v);

                            
    
    std::string determine_comuter_type(std::vector<int> path);
    void update_flow_on_paths(std::vector<int> old_path, std::vector<int> new_path);
    void update_flow_all_edges();
    
        // data
    int number_of_subgraphs;
    int size_of_subgraphs;
    std::vector<int> homeOptions = {0,15,16,17};
    std::vector<int> workOptions = {14};
    std::vector<std::string> transport_types = {"bike","public","car","bike-public","public-bike","car-public","walk"};
    std::vector<std::string> subgraph_types = {"bike","public","car","bike-public","public-bike","car-public"};
    std::unordered_set<std::string> subgraph_types_set = {"bike","public","car","bike-public","public-bike","car-public"};
    
    
    // std::unordered_map<int, std::vector<std::tuple<int,double,std::string>>> adjList; // old

    
private:
    
    std::unordered_map<int, std::unordered_map<int, std::tuple<double, std::string, int, int, int, double>>> adjList;
    // u -> v -> info = (base_weight, type, flow, flow_new, capacity, weighted_weight)
    // dijkstra calculates with weighted weight.

    std::unordered_map<int, std::vector<int>> equivaleny_of_verticies; // here the first entry of #2 should always be equal to #1 also
                                                                       // in total #2 should have as many entries as this->size_of_subgraphs
};


Graph create_test_graph();

Graph create_test_graph_large();

/*
 
class Bruecke{
public:
    double laenge;
    double breite;
    std::vector<Autos> AutosAufBrücke;
}

class Autos{
    
}

*/


/*
 
class Mensch{
 
 ist_wach; // == TRUE oder == FALSE
 position;
 alter;
 geschlecht;
 gewicht;
 function() postion,alter,geschlecht -> abendessen
 function essen -> neues gewicht
 
}
 
Menschen = std::vector<Mensch>;
 
Menschen["rosa"].position += ;
 
for (Mensch in Menschen){
  function2( Mensch.function ) ;
 }


 
*/


#endif // graph.h

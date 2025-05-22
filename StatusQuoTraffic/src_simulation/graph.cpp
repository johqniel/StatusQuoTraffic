//
//  graph.cpp
//  BridgeModel
//
//  Created by nielo on 21.04.25.
//

// tests

#include "graph.h"
#include "iostream"
#include "utilities.h"
#include <fstream>




void Graph::addEdge(int u, int v, double weight, std::string type, int flow, int flow_new, int capacity) {
    std::cout << "Added edge:      " << u%size_of_subgraphs << " -> " << v%size_of_subgraphs << "      type: " << type << "      subgraph: " << u/size_of_subgraphs << " -> " << v/size_of_subgraphs << std::endl;
    
    // Add edge to itself for each vert that is not part of the graph yet to make sure that no
    // unintentional edges are added
    if (adjList.find(u) == adjList.end()){
        adjList[u][u] = {0,"none",0,0,0,0};
    }
    if (adjList.find(v) == adjList.end()){
        adjList[v][v] = {0,"none",0,0,0,0};
    }
    
    
    if (type == "" || type == " "){
        std::cout << "empty type" << std::endl;
        type = "None";
    }
    adjList[u][v] = {weight,type,flow, flow_new, capacity, weight};
}


int Graph::size(){
    return(static_cast<int>(this->adjList.size()));
}

// Change the weight of a specific edge (u -> v), first checks if edge exists, to not add an extra edge that didnt exist before
bool Graph::changeEdgeWeightCHECK(int u, int v, double newWeight) {
    // Check if the node u exists and if it has an edge to v
    if (adjList.find(u) != adjList.end() && adjList[u].find(v) != adjList[u].end()) {
        // Update the weight of the edge using std::get<0>(tuple) to access the weight
        std::get<0>(adjList[u][v]) = newWeight; // Update the weight (first element of tuple)
        return true; // Successfully changed the weight
    }
    return false; // Edge not found
}
// Change the weight of a specific edge (u -> v) without checking if edge exists already
void Graph::changeEdgeWeightFAST(int u, int v, double newWeight) {
    std::get<0>(adjList[u][v]) = newWeight; // Update the weight (first element of tuple)
}
// Change the flow of a specific edge (u -> v), first checks if edge exists, to not add an extra edge that didnt exist before
bool Graph::changeEdgeFlowCHECK(int u, int v, int new_Flow) {
    // Check if the node u exists and if it has an edge to v
    if (adjList.find(u) != adjList.end() && adjList[u].find(v) != adjList[u].end()) {
        // Update the weight of the edge using std::get<0>(tuple) to access the weight
        std::get<3>(adjList[u][v]) = new_Flow; // Update the weight (first element of tuple)
        if (new_Flow > std::get<4>(adjList[u][v])){
            // update weighted weight
            int capacity = std::get<4>(adjList[u][v]);
            if (capacity == 0){
                std::cout << "capacity is equal to 0" << std::endl;
                return false;
            }
            std::get<5>(adjList[u][v]) = (new_Flow / capacity) * std::get<0>(adjList[u][v]);
        }
        else{
            std::get<5>(adjList[u][v]) = std::get<0>(adjList[u][v]);
        }
        return true; // Successfully changed the weight
    }
    return false; // Edge not found
}
// Change the flow of a specific edge (u -> v) without checking if edge exists already
void Graph::changeEdgeFlowFAST(int u, int v, int new_Flow) {
    std::get<3>(adjList[u][v]) = new_Flow; // Update the weight (first element of tuple)
    if (new_Flow > std::get<4>(adjList[u][v])){
        // update weighted weight
        int capacity = std::get<4>(adjList[u][v]);
        if (capacity == 0){
            std::cout << "capacity is equal to 0" << std::endl;
            return;
        }
        std::get<5>(adjList[u][v]) = (new_Flow / capacity) * std::get<0>(adjList[u][v]);
    }
    else{
        std::get<5>(adjList[u][v]) = std::get<0>(adjList[u][v]);
    }
}

void Graph::increaseNewFlowFAST(int u, int v){
    //std::cout << "new flow increased on edge: " << u << "-" << v << std::endl;
    std::get<3>(adjList[u][v]) += 1; // Update the weight (first element of tuple)
    int new_Flow = std::get<3>(adjList[u][v]);
    if (new_Flow > std::get<4>(adjList[u][v])){
        // update weighted weight
        int capacity = std::get<4>(adjList[u][v]);
        if (capacity == 0){
            std::cout << "capacity is equal to 0" << std::endl;
            return;
        }
        std::get<5>(adjList[u][v]) = (new_Flow / capacity) * std::get<0>(adjList[u][v]);
    }
    else{
        std::get<5>(adjList[u][v]) = std::get<0>(adjList[u][v]);
    }
}

void Graph::decreaseNewFlowFAST(int u, int v){
    std::get<3>(adjList[u][v]) -= 1; // Update the weight (first element of tuple)
    int new_Flow = std::get<3>(adjList[u][v]);
    if (new_Flow > std::get<4>(adjList[u][v])){
        // update weighted weight
        int capacity = std::get<4>(adjList[u][v]);
        if (capacity == 0){
            std::cout << "capacity is equal to 0" << std::endl;
            return;
        }
        std::get<5>(adjList[u][v]) = (new_Flow / capacity) * std::get<0>(adjList[u][v]);
    }
    else{
        std::get<5>(adjList[u][v]) = std::get<0>(adjList[u][v]);
    }
}
//bool changeEdgeFlowFAST(int u, int v, double new_flow);
//bool changeEdgeFlowCHECK(int u, int v, double new_flow);





std::vector<int> Graph::dijkstra(int source, int target) {
    // the path that is returned later
    std::vector<int> path;
    // known shortest distance from source to other nodes
    std::unordered_map<int,double> distance;
    // map that stores previous node in path
    std:: unordered_map<int,int> previous;

    auto compare = [](const std::pair<int, double>& a, const std::pair<int,double>& b){
        return a.second > b.second;
    };
    
    // priority queue for closest nodes
    std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, decltype(compare)> pq(compare);
    
    
    // initilize distance function to infinity
    for (const auto& node: adjList){
        distance[node.first] = std::numeric_limits<int>::max();
    }
    distance[target] = std::numeric_limits<int>::max();
    
    //std::cout << " the distance map after initialization is: " << std::endl;
    //print_int_map(distance);
    
    // distance to source node is 0 // add to priority queue
    
    distance[source] = 0;
    pq.push({source,0});
    
    previous[source] = source;
    
    // loop to search graph
    
    while(!pq.empty()){
        
        int u = pq.top().first; // node with smallest distance to explored graph
        //std::cout << "vert " << u << " was popped from queue." << std::endl;
        pq.pop(); // remove that node from queue
        if (u == target){
            //std::cout << "target was popped from queue." << std::endl;
            break;
        }
        
        // for later
        //previous[u] = u;
        // explore neighbours of node u

        for( const auto& [v, info] : adjList[u]){
            //std::cout << v << " is neighbour of " << u << std::endl;
            double weight = std::get<5>(info); // distance to that node
            
            int alt = distance[u] + weight; // calculate weight to reach that node via u from source
            
            //std::cout << "new potential distance is: " << alt << " old distance is: " << distance[v] << std::endl;
            
            if (alt < distance[v]){ // if new weight is smaller:
                //std::cout << "new distance smaller for vert: " << v << " from vert " << u << std::endl;
                distance[v] = alt;
                previous[v] = u;        // keep track of path
                //std::cout << "previous updated: " << v << ", " << u << std::endl;
                pq.push({v,alt});   // add neighbor to queue
            }
        }
    }
    
    int u = target;
    
    //print_int_map(previous);
    
    while(!(previous[u] == u)){
        path.push_back(u);
        u = previous[u];
    }
    path.push_back(u);

    //print_int_vector(path);
    //std::cout << "length of path from " << source << " to " << target << " = " << path.size() << std::endl;
    return path;
}



// Implementing an extra dijkstra algorithm was a huuuge waste of time!!

/*
 
 std::vector<int> Graph::dijkstra_flow(int source, int target) {
     // the path that is returned later
     std::vector<int> path;
     // known shortest distance from source to other nodes
     std::unordered_map<int, double> distance;
     // map that stores previous node in path
     std::unordered_map<int, int> previous;

     // CORRECTED: The compare function should only compare the 'distance' (second element of the pair).
     // The flow/capacity logic belongs when traversing edges, not comparing nodes in the PQ.
     auto compare = [](const std::pair<int, double>& a, const std::pair<int, double>& b) {
         return a.second > b.second; // Min-priority queue based on distance
     };

     // priority queue for closest nodes
     // Note: The pair should be {distance, node_id} for a min-priority queue if you want to use default comparison,
     // or {node_id, distance} with a custom comparator that correctly sorts by distance.
     // Your current setup with {node_id, distance} and `a.second > b.second` is correct for a min-PQ.
     std::priority_queue<std::pair<int, double>, std::vector<std::pair<int, double>>, decltype(compare)> pq(compare);

     // Initialize distance function to infinity for all known nodes
     // Iterate through adjList to get all nodes that exist in the graph
     for (const auto& pair : adjList) {
         distance[pair.first] = std::numeric_limits<double>::max(); // Use double for max value
         // Also initialize distances for neighbors if they are not source/target
         for (const auto& inner_pair : pair.second) {
             distance[inner_pair.first] = std::numeric_limits<double>::max();
         }
     }
     // Ensure source and target are in distance map, even if isolated
     distance[source] = std::numeric_limits<double>::max();
     distance[target] = std::numeric_limits<double>::max();


     // Distance to source node is 0; add to priority queue
     distance[source] = 0.0; // Ensure it's a double
     pq.push({source, 0.0}); // Ensure it's a double

     previous[source] = source; // Source is its own predecessor for path reconstruction

     // Loop to search graph
     while (!pq.empty()) {
         int u = pq.top().first; // Node with smallest distance from source
         double current_dist_u = pq.top().second; // Current shortest distance to u

         pq.pop(); // Remove that node from queue

         // Optimization: if we already found a shorter path to u, skip this entry
         if (current_dist_u > distance[u]) {
             continue;
         }

         if (u == target) {
             break; // Found the shortest path to the target
         }

         // Explore neighbors of node u
         // IMPORTANT: Ensure adjList[u] does not implicitly add 'u' if it's not a valid node.
         // Your previous fix (adding self-loop) should handle this, but a check is safer.
         if (adjList.find(u) == adjList.end()) {
             continue; // Node u has no outgoing edges (or doesn't exist in adjList)
         }

         for (const auto& [v, edge_data] : adjList[u]) {
             double base_weight = std::get<0>(edge_data); // Base weight of the edge (u,v)
             // std::string type = std::get<1>(edge_data); // Not used in weight calculation
             int flow = std::get<2>(edge_data);
             // int flow_new = std::get<3>(edge_data); // Not used in weight calculation
             int capacity = std::get<4>(edge_data);

             // Calculate the effective weight of the edge (u,v) using flow/capacity
             double effective_edge_weight;
             if (capacity > 0) {
                 effective_edge_weight = base_weight * (1.0 + 2.0 * (static_cast<double>(flow) / capacity));
             } else {
                 // Handle zero capacity: either make it infinitely expensive or use base weight
                 // For Dijkstra, if capacity is 0, it means no flow, so it should be very expensive
                 effective_edge_weight = std::numeric_limits<double>::max();
             }

             // Calculate new potential distance to neighbor 'v' via 'u'
             double alt = distance[u] + effective_edge_weight;

             // If a shorter path to 'v' is found
             if (alt < distance[v]) {
                 distance[v] = alt;     // Update shortest distance to 'v'
                 previous[v] = u;       // Set 'u' as predecessor of 'v'
                 pq.push({v, alt});     // Add neighbor 'v' to queue with its new total distance
             }
         }
     }

     // Reconstruct the path from target to source
     int current_node = target;
     // Check if target is reachable (distance is not infinity)
     if (distance[target] == std::numeric_limits<double>::max()) {
         return path; // Return empty path if target is unreachable
     }

     while (current_node != source) {
         path.push_back(current_node);
         // Check if current_node has a predecessor (prevents infinite loop for unreachable nodes)
         if (previous.find(current_node) == previous.end()) {
             path.clear(); // Path is broken, clear it
             return path;
         }
         current_node = previous[current_node];
     }
     path.push_back(source); // Add the source node
     std::reverse(path.begin(), path.end()); // Reverse to get path from source to target

     return path;
 }di
 
 
 */


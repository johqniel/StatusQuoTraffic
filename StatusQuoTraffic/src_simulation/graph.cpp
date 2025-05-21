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
    std::cout << "Added edge from " << u << " to " << v << " type is " << type << std::endl;
    if (adjList.find(u) == adjList.end()){
        adjList[u][u] = {0,"none",0,0,0};
    }
    if (adjList.find(v) == adjList.end()){
        adjList[v][v] = {0,"none",0,0,0};
    }
    if (type == "" || type == " "){
        std::cout << "empty type" << std::endl;
        type = "None";
    }
    adjList[u][v] = {weight,type,flow, flow_new, capacity};
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
        return true; // Successfully changed the weight
    }
    return false; // Edge not found
}
// Change the flow of a specific edge (u -> v) without checking if edge exists already
void Graph::changeEdgeFlowFAST(int u, int v, int new_Flow) {
    std::get<3>(adjList[u][v]) = new_Flow; // Update the weight (first element of tuple)
}

void Graph::increaseNewFlowFAST(int u, int v){
    //std::cout << "new flow increased on edge: " << u << "-" << v << std::endl;
    std::get<3>(adjList[u][v]) += 1; // Update the weight (first element of tuple)

}

void Graph::decreaseNewFlowFAST(int u, int v){
    std::get<3>(adjList[u][v]) -= 1; // Update the weight (first element of tuple)
}
//bool changeEdgeFlowFAST(int u, int v, double new_flow);
//bool changeEdgeFlowCHECK(int u, int v, double new_flow);


std::vector<int> Graph::dijkstra_flow(int source, int target) {
    // the path that is returned later
    std::vector<int> path;
    // known shortest distance from source to other nodes
    std::unordered_map<int,double> distance;
    // map that stores previous node in path
    std:: unordered_map<int,int> previous;

    auto compare = [this](const std::pair<int, double>& a, const std::pair<int, double>& b) {
        int u = a.first;
        double weight_a = a.second;
        int v = b.first;
        double weight_b = b.second;
        
        // Get the flow and capacity
        int flow_a = std::get<2>(adjList[u][v]);
        int capacity_a = std::get<4>(adjList[u][v]);
        
        int flow_b = std::get<2>(adjList[v][u]);
        int capacity_b = std::get<4>(adjList[v][u]);
        
        // Calculate utilization
        double utilization_a = (capacity_a > 0) ? (double)flow_a / capacity_a : 0;
        double utilization_b = (capacity_b > 0) ? (double)flow_b / capacity_b : 0;
        
        // Add a penalty based on the utilization (tweak this multiplier as needed)
        double effective_weight_a = weight_a * (1 + 2 * utilization_a);
        double effective_weight_b = weight_b * (1 + 2 * utilization_b);
        
        return effective_weight_a > effective_weight_b;
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
            double weight = std::get<0>(info); // distance to that node
            
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
            double weight = std::get<0>(info); // distance to that node
            
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



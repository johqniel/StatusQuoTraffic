//
//  utilities.cpp
//  BridgeModel
//
//  Created by nielo on 03.05.25.
//

#include "utilities.h"
#include "iostream"
#include <random>
#include <ctime>

void print_int_vector(std::vector<int> vector_to_print , std::string message){
    // std::cout << "we are in print int vector function" << std::endl;
    std::cout << message << " ";
    for (int num : vector_to_print) {
            std::cout << num << " ";
        }

        std::cout << std::endl;
}

void print_int_map(const std::unordered_map<int, int>& map) {
    for (const auto& pair : map) {
        std::cout << "Key: " << pair.first << ", Value: " << pair.second << std::endl;
    }
}

std::vector<double> generate_random_doubles(int num_subgraphs, double min, double max) {
    std::vector<double> random_doubles(num_subgraphs);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(min, max);
    
    for (int i = 0; i < num_subgraphs; ++i) {
        random_doubles[i] = dist(gen);
    }
    return random_doubles;
}

double generate_random_double(double min, double max){
    // Create a random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(min, max);  // Range [0, 4]

    // Generate a random double
    double random_double = dist(gen);
    return random_double;
}

int generate_random_unsigned(int n){
    // Create a random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, n);  // Range [0, n]

    // Generate a random unsigned integer
    int random_unsigned = dist(gen);
    return random_unsigned;
}

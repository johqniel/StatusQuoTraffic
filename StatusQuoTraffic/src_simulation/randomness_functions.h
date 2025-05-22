//
//  randomness_functions.h
//  StatusQuoTraffic
//
//  Created by nielo on 22.05.25.
//

#include <iostream> // For input/output operations (e.g., std::cout)
#include <vector>   // For using std::vector to store options
#include <string>   // For using std::string for agent type
#include <random>   // For random number generation (std::mt19937, std::uniform_int_distribution)
#include <chrono>   // For seeding the random number generator with current time

// Define a structure to hold the agent's profile
struct AgentProfile {
    int home;         // The agent's home location (integer ID)
    int work;         // The agent's work location (integer ID)
    std::string type; // The agent's type (e.g., "worker", "student")

    // A helper function to print the agent's profile
    void print() const {
        std::cout << "Agent Profile:" << std::endl;
        std::cout << "  Home: " << home << std::endl;
        std::cout << "  Work: " << work << std::endl;
        std::cout << "  Type: " << type << std::endl;
    }
    

};

AgentProfile generateRandomAgentProfile(const std::vector<int>& homeOptions,
                                        const std::vector<int>& workOptions,
                                        const std::vector<std::string>& typeOptions);

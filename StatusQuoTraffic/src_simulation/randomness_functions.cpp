//
//  randomness_functions.cpp
//  StatusQuoTraffic
//
//  Created by nielo on 22.05.25.
//


#include "randomness_functions.h"



/**
 * @brief Generates a random profile for an agent based on provided options.
 *
 * This function takes three non-empty vectors of options for home, work, and type.
 * It randomly selects one option from each vector to create an AgentProfile.
 *
 * @param homeOptions A non-empty vector of integer options for the agent's home.
 * @param workOptions A non-empty vector of integer options for the agent's work.
 * @param typeOptions A non-empty vector of string options for the agent's type.
 * @return An AgentProfile struct with randomly selected home, work, and type.
 * @throws std::invalid_argument if any of the input vectors are empty.
 */
AgentProfile generateRandomAgentProfile(
    const std::vector<int>& homeOptions,
    const std::vector<int>& workOptions,
    const std::vector<std::string>& typeOptions) {

    // Input validation: Ensure all option vectors are non-empty
    if (homeOptions.empty()) {
        throw std::invalid_argument("Home options vector cannot be empty.");
    }
    if (workOptions.empty()) {
        throw std::invalid_argument("Work options vector cannot be empty.");
    }
    if (typeOptions.empty()) {
        throw std::invalid_argument("Type options vector cannot be empty.");
    }

    // Initialize a random number generator engine
    // std::mt19937 is a Mersenne Twister pseudo-random number generator,
    // generally preferred over std::rand() for better statistical properties.
    // We seed it with the current time to ensure different sequences each run.
    std::mt19937 rng(std::chrono::high_resolution_clock::now().time_since_epoch().count());

    // Create uniform integer distributions for selecting indices from the vectors
    // The range for the distribution is [0, vector_size - 1]
    std::uniform_int_distribution<int> homeDist(0, homeOptions.size() - 1);
    std::uniform_int_distribution<int> workDist(0, workOptions.size() - 1);
    std::uniform_int_distribution<int> typeDist(0, typeOptions.size() - 1);

    // Randomly select an index for each attribute
    int randomHomeIndex = homeDist(rng);
    int randomWorkIndex = workDist(rng);
    int randomTypeIndex = typeDist(rng);

    // Create and return the AgentProfile using the randomly selected options
    return AgentProfile{
        homeOptions[randomHomeIndex],
        workOptions[randomWorkIndex],
        typeOptions[randomTypeIndex]
    };
}

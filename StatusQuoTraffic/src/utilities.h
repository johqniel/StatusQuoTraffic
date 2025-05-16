//
//  utilities.h
//  BridgeModel
//
//  Created by nielo on 03.05.25.
//


#ifndef UTILITIES_H
#define UTILITIES_H

#include <vector>
#include <queue>


void print_int_vector(std::vector<int> vector_to_print, std::string message = "");  // Declare the function you want to use in main.cpp

void print_int_map(const std::unordered_map<int, int>& map);

std::vector<double> generate_random_doubles(int num_subgraphs, double min = 0.0, double max = 4.0);

double generate_random_double(double min = 0.0, double max = 4.0);

int generate_random_unsigned(int n = 10);

#endif

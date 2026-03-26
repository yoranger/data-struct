#ifndef KNAPSACK_H
#define KNAPSACK_H

#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <sstream>

// A structure to represent an item
struct Item {
    int weight;
    int value;
    double ratio;  // value/weight ratio
};

// Function to compare two items based on their value-to-weight ratio
bool compare(Item a, Item b);

// Function to calculate the maximum value of the fractional knapsack
double fractionalKnapsack(int W, std::vector<Item>& items, int n);

#endif

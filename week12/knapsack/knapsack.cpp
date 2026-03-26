#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include "knapsack.h"

using namespace std;

// Function to compare two items based on their value-to-weight ratio
bool compare(Item a, Item b) {
    return a.ratio > b.ratio;
}

double fractionalKnapsack(int W, vector<Item>& items, int n) {
    // Sort items based on value/weight ratio in descending order
    for (int i = 0; i < n; i++) {
        items[i].ratio = (double)items[i].value / items[i].weight;
    }
    sort(items.begin(), items.end(), compare);

    double totalValue = 0.0;

    // TODO iterate through n and calculate total value
    for (int i = 0; i < n; ++i)
    {
        if(items[i].weight >= W)
        {
            totalValue += items[i].ratio * W;
            break;
        }
        else
        {
            totalValue += items[i].value;
            W -= items[i].weight;
        }
    }

    return totalValue;
}

int main() {
    int n, W;
    cout << "Enter number of items and knapsack capacity, separated by space: ";
    cin >> n >> W;
    
    vector<Item> items(n);

    // Take the list of weights as space-separated input
    cout << "Enter the weights for each item (separated by spaces): ";
    cin.ignore();  // To ignore any newline left in the input buffer
    string weightInput;
    getline(cin, weightInput);
    stringstream ss(weightInput);
    
    // Fill the weight array
    for (int i = 0; i < n; i++) {
        ss >> items[i].weight;
    }

    // Take the list of values as space-separated input
    cout << "Enter the values for each item (separated by spaces): ";
    string valueInput;
    getline(cin, valueInput);
    stringstream ssValue(valueInput);
    
    // Fill the value array
    for (int i = 0; i < n; i++) {
        ssValue >> items[i].value;
    }

    double maxValue = fractionalKnapsack(W, items, n);

    cout << "Maximum value that can be carried: " << fixed << setprecision(2) << maxValue << endl;

    return 0;
}
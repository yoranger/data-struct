#include<iostream>
#include "majority_element.h"

using namespace std;

int main() {
    vector<int> nums = {1, 2, 3, 4, 5, 5, 5, 5, 5};
    cout << findMajority(nums) << '\n';
    return 0;
}
#include <iostream>
int calculateProgressionPaths(int n) {
    int totalVal = 0;
    if(n > 1)
    {
        totalVal += calculateProgressionPaths(n - 1);
        totalVal += calculateProgressionPaths(n - 2);
    }
    else if(n != 0)
    {
        ++totalVal;
    }
    if(n == 0)
        ++totalVal;

    return totalVal;
}
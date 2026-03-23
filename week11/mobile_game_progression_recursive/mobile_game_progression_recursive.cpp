#include <iostream>
int calculateProgressionPaths(int n) {
    if (n == 1)
        return 1;
    if (n == 2)
        return 2;

    return calculateProgressionPaths(n - 1) + calculateProgressionPaths(n - 2);

    // int totalVal = 0;
    // if(n > 1)
    // {
    //     totalVal += calculateProgressionPaths(n - 1);
    //     totalVal += calculateProgressionPaths(n - 2);
    // }
    // else if(n != 0)
    // {
    //     ++totalVal;
    // }
    // if(n == 0)
    //     ++totalVal;

    // return totalVal;
}
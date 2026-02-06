#include <unordered_map>
#include <vector>

int findMajority(std::vector<int>& nums) {
    // YOUR CODE GOES HERE
    std::unordered_map<int,int> val;
    for(int num : nums)
    {
        ++val[num];
    }
    bool same = false;
    int amt = 0;
    int final = 0;
    for (std::pair<int, int> num : val)
    {
        if(amt < num.second)
        {
            amt = num.second;
            final = num.first;
            same = false;
        }
        else if(amt == num.second)
        {
            same = true;
        }
    }
    if(!same && amt > (int)nums.size() / 2)
        return final;
    return -1;
}
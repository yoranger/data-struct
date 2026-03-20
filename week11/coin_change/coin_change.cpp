#include <vector>
int coinChange(std::vector<int>& coins, int amount) {
    std::vector<int> dp(amount + 1, amount + 1);
    dp[0] = 0;
    for (int i = 1; i <= amount; i++) {
        for (int c : coins) {
            if (c <= i && dp[i - c] + 1 < dp[i]) {
                dp[i] = dp[i - c] + 1;
            }
        }
    }
    return dp[amount] > amount ? -1 : dp[amount];
}
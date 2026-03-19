#include <string>
#include<vector>
#include<iostream>
// int longestCommonSubsequence(std::string dna1, std::string dna2) {
//     int const len1 = dna1.size(), len2 = dna2.size();
//     std::vector<std::vector<int>> total(len1 + 1, std::vector<int>(len2 + 1, 0));


//     for (int i = 1; i < len1 + 1; ++i)
//     {
//         for (int j = 1; j < len2 + 1; ++j)
//         {
//             total[i][j] = std::max(std::max(total[i - 1][j], total[i][j - 1]), total[i - 1][j - 1]);
//             if (dna1[i -1] == dna2[j-1])
//             {
//                 if(i < (len1 + 1) && j < (len2 + 1))
//                 {
//                     ++total[i][j];
//                     ++i;
//                 }
//                 //total[i][j] = 1 + total[i - 1][j - 1]; // Characters match
//             }   
            
//         }
//     }
//     return total[len1][len2];
// }
int longestCommonSubsequence(std::string dna1, std::string dna2) {
    int m = dna1.size();
    int n = dna2.size();
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (dna1[i - 1] == dna2[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1]; // Characters match
            } else {
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]); // Take max of previous
            }
        }
    }

    return dp[m][n]; // Length of LCS
}
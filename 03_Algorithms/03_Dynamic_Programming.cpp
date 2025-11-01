/*
 * ZCO PREPARATION - ALGORITHMS: Dynamic Programming
 * 
 * Dynamic Programming patterns and common problems
 * Critical for solving optimization problems
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <cstring>
using namespace std;

// ===== MEMOIZATION HELPER =====
// Use map or array for memoization

// ===== 1. FIBONACCI (BASIC DP) =====

// Recursive (slow) - O(2^n)
int fibRecursive(int n) {
    if(n <= 1) return n;
    return fibRecursive(n - 1) + fibRecursive(n - 2);
}

// Memoization - O(n)
int fibMemo(int n, vector<int> &memo) {
    if(n <= 1) return n;
    if(memo[n] != -1) return memo[n];
    return memo[n] = fibMemo(n - 1, memo) + fibMemo(n - 2, memo);
}

// Tabulation - O(n)
int fibDP(int n) {
    if(n <= 1) return n;
    vector<int> dp(n + 1);
    dp[0] = 0;
    dp[1] = 1;
    
    for(int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    
    return dp[n];
}

// Space optimized - O(1) space
int fibSpaceOpt(int n) {
    if(n <= 1) return n;
    int prev = 0, curr = 1;
    for(int i = 2; i <= n; i++) {
        int next = prev + curr;
        prev = curr;
        curr = next;
    }
    return curr;
}

// ===== 2. CLIMBING STAIRS =====
// Ways to reach nth step (1 or 2 steps at a time)

int climbStairs(int n) {
    if(n <= 2) return n;
    vector<int> dp(n + 1);
    dp[1] = 1;
    dp[2] = 2;
    
    for(int i = 3; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    
    return dp[n];
}

// ===== 3. HOUSE ROBBER =====
// Maximum money without robbing adjacent houses

int houseRobber(vector<int> &nums) {
    int n = nums.size();
    if(n == 0) return 0;
    if(n == 1) return nums[0];
    
    vector<int> dp(n);
    dp[0] = nums[0];
    dp[1] = max(nums[0], nums[1]);
    
    for(int i = 2; i < n; i++) {
        dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
    }
    
    return dp[n - 1];
}

// ===== 4. COIN CHANGE (COUNT WAYS) =====
// Number of ways to make amount

int coinChangeWays(vector<int> &coins, int amount) {
    vector<int> dp(amount + 1, 0);
    dp[0] = 1;  // One way to make 0
    
    for(int coin : coins) {
        for(int i = coin; i <= amount; i++) {
            dp[i] += dp[i - coin];
        }
    }
    
    return dp[amount];
}

// ===== 5. COIN CHANGE (MINIMUM COINS) =====
// Minimum coins to make amount

int coinChangeMin(vector<int> &coins, int amount) {
    vector<int> dp(amount + 1, amount + 1);
    dp[0] = 0;
    
    for(int i = 1; i <= amount; i++) {
        for(int coin : coins) {
            if(coin <= i) {
                dp[i] = min(dp[i], dp[i - coin] + 1);
            }
        }
    }
    
    return (dp[amount] > amount) ? -1 : dp[amount];
}

// ===== 6. LONGEST INCREASING SUBSEQUENCE (LIS) =====
// O(n^2) solution

int lengthOfLIS(vector<int> &nums) {
    int n = nums.size();
    vector<int> dp(n, 1);
    
    for(int i = 1; i < n; i++) {
        for(int j = 0; j < i; j++) {
            if(nums[j] < nums[i]) {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }
    
    return *max_element(dp.begin(), dp.end());
}

// LIS O(n log n) using binary search
int lengthOfLISFast(vector<int> &nums) {
    vector<int> tails;  // Smallest tail of all increasing subsequences
    
    for(int num : nums) {
        auto it = lower_bound(tails.begin(), tails.end(), num);
        if(it == tails.end()) {
            tails.push_back(num);
        } else {
            *it = num;
        }
    }
    
    return tails.size();
}

// ===== 7. LONGEST COMMON SUBSEQUENCE (LCS) =====

int longestCommonSubsequence(string text1, string text2) {
    int m = text1.length(), n = text2.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    
    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            if(text1[i - 1] == text2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    
    return dp[m][n];
}

// ===== 8. EDIT DISTANCE =====
// Minimum operations to convert string1 to string2

int editDistance(string word1, string word2) {
    int m = word1.length(), n = word2.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));
    
    // Base cases
    for(int i = 0; i <= m; i++) dp[i][0] = i;
    for(int j = 0; j <= n; j++) dp[0][j] = j;
    
    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            if(word1[i - 1] == word2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = 1 + min({
                    dp[i - 1][j],      // Delete
                    dp[i][j - 1],      // Insert
                    dp[i - 1][j - 1]   // Replace
                });
            }
        }
    }
    
    return dp[m][n];
}

// ===== 9. 0/1 KNAPSACK =====
// Maximum value with weight constraint

int knapsack01(vector<int> &weights, vector<int> &values, int capacity) {
    int n = weights.size();
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));
    
    for(int i = 1; i <= n; i++) {
        for(int w = 1; w <= capacity; w++) {
            if(weights[i - 1] <= w) {
                dp[i][w] = max(
                    dp[i - 1][w],  // Don't take
                    dp[i - 1][w - weights[i - 1]] + values[i - 1]  // Take
                );
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }
    
    return dp[n][capacity];
}

// Space optimized knapsack
int knapsack01SpaceOpt(vector<int> &weights, vector<int> &values, int capacity) {
    vector<int> dp(capacity + 1, 0);
    
    for(int i = 0; i < weights.size(); i++) {
        for(int w = capacity; w >= weights[i]; w--) {
            dp[w] = max(dp[w], dp[w - weights[i]] + values[i]);
        }
    }
    
    return dp[capacity];
}

// ===== 10. UNBOUNDED KNAPSACK =====
// Items can be used multiple times

int unboundedKnapsack(vector<int> &weights, vector<int> &values, int capacity) {
    vector<int> dp(capacity + 1, 0);
    
    for(int w = 1; w <= capacity; w++) {
        for(int i = 0; i < weights.size(); i++) {
            if(weights[i] <= w) {
                dp[w] = max(dp[w], dp[w - weights[i]] + values[i]);
            }
        }
    }
    
    return dp[capacity];
}

// ===== 11. PARTITION EQUAL SUBSET SUM =====
// Check if array can be partitioned into two equal sum subsets

bool canPartition(vector<int> &nums) {
    int sum = 0;
    for(int num : nums) sum += num;
    
    if(sum % 2 != 0) return false;
    
    int target = sum / 2;
    vector<bool> dp(target + 1, false);
    dp[0] = true;
    
    for(int num : nums) {
        for(int i = target; i >= num; i--) {
            dp[i] = dp[i] || dp[i - num];
        }
    }
    
    return dp[target];
}

// ===== 12. PALINDROME PARTITIONING (MIN CUTS) =====
// Minimum cuts to partition string into palindromes

int minCut(string s) {
    int n = s.length();
    vector<vector<bool>> isPal(n, vector<bool>(n, false));
    vector<int> dp(n);
    
    // Precompute palindromes
    for(int i = 0; i < n; i++) {
        isPal[i][i] = true;
    }
    
    for(int i = 0; i < n - 1; i++) {
        if(s[i] == s[i + 1]) {
            isPal[i][i + 1] = true;
        }
    }
    
    for(int len = 3; len <= n; len++) {
        for(int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            if(s[i] == s[j] && isPal[i + 1][j - 1]) {
                isPal[i][j] = true;
            }
        }
    }
    
    // DP for minimum cuts
    for(int i = 0; i < n; i++) {
        if(isPal[0][i]) {
            dp[i] = 0;
        } else {
            dp[i] = i;
            for(int j = 1; j <= i; j++) {
                if(isPal[j][i]) {
                    dp[i] = min(dp[i], dp[j - 1] + 1);
                }
            }
        }
    }
    
    return dp[n - 1];
}

// ===== 13. MAXIMUM SUM SUBARRAY (KADANE'S VARIANT) =====
// Maximum sum with at most k deletions

int maximumSum(vector<int> &nums, int k) {
    // Simplified: Maximum sum deleting at most k elements
    // Use DP with state (index, deletions used)
    
    int n = nums.size();
    vector<vector<int>> dp(n + 1, vector<int>(k + 1, INT_MIN));
    dp[0][0] = 0;
    
    for(int i = 1; i <= n; i++) {
        for(int d = 0; d <= k; d++) {
            // Don't delete current
            if(dp[i - 1][d] != INT_MIN) {
                dp[i][d] = max(dp[i][d], dp[i - 1][d] + nums[i - 1]);
            }
            // Delete current (if deletions left)
            if(d > 0 && dp[i - 1][d - 1] != INT_MIN) {
                dp[i][d] = max(dp[i][d], dp[i - 1][d - 1]);
            }
        }
    }
    
    int result = INT_MIN;
    for(int d = 0; d <= k; d++) {
        result = max(result, dp[n][d]);
    }
    
    return result;
}

// ===== MAIN FUNCTION =====
int main() {
    // Fibonacci
    cout << "Fibonacci(10): " << fibDP(10) << endl;
    
    // Coin Change
    vector<int> coins = {1, 2, 5};
    cout << "Ways to make 11: " << coinChangeWays(coins, 11) << endl;
    cout << "Min coins for 11: " << coinChangeMin(coins, 11) << endl;
    
    // LIS
    vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};
    cout << "LIS length: " << lengthOfLIS(nums) << endl;
    
    // LCS
    string s1 = "abcde", s2 = "ace";
    cout << "LCS length: " << longestCommonSubsequence(s1, s2) << endl;
    
    // Knapsack
    vector<int> weights = {1, 3, 4, 5};
    vector<int> values = {1, 4, 5, 7};
    cout << "Knapsack value: " << knapsack01(weights, values, 7) << endl;
    
    return 0;
}


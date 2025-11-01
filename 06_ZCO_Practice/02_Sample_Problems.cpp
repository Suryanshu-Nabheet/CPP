/*
 * ZCO PREPARATION - SAMPLE PROBLEMS
 * 
 * Common problem patterns and solutions
 * Practice these patterns for ZCO
 */

#include <bits/stdc++.h>
using namespace std;

// ===== PROBLEM 1: TWO SUM =====
// Find two numbers that add up to target

vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> seen;
    
    for(int i = 0; i < nums.size(); i++) {
        int complement = target - nums[i];
        if(seen.find(complement) != seen.end()) {
            return {seen[complement], i};
        }
        seen[nums[i]] = i;
    }
    
    return {};
}

// ===== PROBLEM 2: MAXIMUM SUBARRAY SUM (KADANE'S) =====
int maxSubArray(vector<int>& nums) {
    int maxSum = nums[0];
    int currentSum = nums[0];
    
    for(int i = 1; i < nums.size(); i++) {
        currentSum = max(nums[i], currentSum + nums[i]);
        maxSum = max(maxSum, currentSum);
    }
    
    return maxSum;
}

// ===== PROBLEM 3: STOCK BUY SELL (MAX PROFIT) =====
int maxProfit(vector<int>& prices) {
    int minPrice = INT_MAX;
    int maxProfit = 0;
    
    for(int price : prices) {
        minPrice = min(minPrice, price);
        maxProfit = max(maxProfit, price - minPrice);
    }
    
    return maxProfit;
}

// ===== PROBLEM 4: VALID PARENTHESES =====
bool isValid(string s) {
    stack<char> st;
    
    for(char c : s) {
        if(c == '(' || c == '[' || c == '{') {
            st.push(c);
        } else {
            if(st.empty()) return false;
            if((c == ')' && st.top() != '(') ||
               (c == ']' && st.top() != '[') ||
               (c == '}' && st.top() != '{')) {
                return false;
            }
            st.pop();
        }
    }
    
    return st.empty();
}

// ===== PROBLEM 5: MERGE SORTED ARRAYS =====
void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    int i = m - 1, j = n - 1, k = m + n - 1;
    
    while(i >= 0 && j >= 0) {
        if(nums1[i] > nums2[j]) {
            nums1[k--] = nums1[i--];
        } else {
            nums1[k--] = nums2[j--];
        }
    }
    
    while(j >= 0) {
        nums1[k--] = nums2[j--];
    }
}

// ===== PROBLEM 6: FIND MISSING NUMBER =====
// Array contains n distinct numbers in range [0, n]
int missingNumber(vector<int>& nums) {
    int n = nums.size();
    int expectedSum = n * (n + 1) / 2;
    int actualSum = 0;
    
    for(int num : nums) {
        actualSum += num;
    }
    
    return expectedSum - actualSum;
}

// Using XOR
int missingNumberXOR(vector<int>& nums) {
    int result = nums.size();
    for(int i = 0; i < nums.size(); i++) {
        result ^= i;
        result ^= nums[i];
    }
    return result;
}

// ===== PROBLEM 7: CONTAINS DUPLICATE =====
bool containsDuplicate(vector<int>& nums) {
    unordered_set<int> seen;
    for(int num : nums) {
        if(seen.find(num) != seen.end()) {
            return true;
        }
        seen.insert(num);
    }
    return false;
}

// ===== PROBLEM 8: ROTATE ARRAY =====
void rotate(vector<int>& nums, int k) {
    int n = nums.size();
    k = k % n;
    
    reverse(nums.begin(), nums.end());
    reverse(nums.begin(), nums.begin() + k);
    reverse(nums.begin() + k, nums.end());
}

// ===== PROBLEM 9: PRODUCT OF ARRAY EXCEPT SELF =====
vector<int> productExceptSelf(vector<int>& nums) {
    int n = nums.size();
    vector<int> result(n, 1);
    
    // Left products
    for(int i = 1; i < n; i++) {
        result[i] = result[i - 1] * nums[i - 1];
    }
    
    // Right products
    int right = 1;
    for(int i = n - 1; i >= 0; i--) {
        result[i] *= right;
        right *= nums[i];
    }
    
    return result;
}

// ===== PROBLEM 10: FIND PEAK ELEMENT =====
int findPeakElement(vector<int>& nums) {
    int left = 0, right = nums.size() - 1;
    
    while(left < right) {
        int mid = left + (right - left) / 2;
        if(nums[mid] < nums[mid + 1]) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    
    return left;
}

// ===== PROBLEM 11: SEARCH IN ROTATED SORTED ARRAY =====
int search(vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;
    
    while(left <= right) {
        int mid = left + (right - left) / 2;
        
        if(nums[mid] == target) return mid;
        
        // Left half is sorted
        if(nums[left] <= nums[mid]) {
            if(target >= nums[left] && target < nums[mid]) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        // Right half is sorted
        else {
            if(target > nums[mid] && target <= nums[right]) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }
    
    return -1;
}

// ===== PROBLEM 12: THREE SUM =====
vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int>> result;
    sort(nums.begin(), nums.end());
    
    for(int i = 0; i < nums.size() - 2; i++) {
        if(i > 0 && nums[i] == nums[i - 1]) continue;
        
        int left = i + 1, right = nums.size() - 1;
        
        while(left < right) {
            int sum = nums[i] + nums[left] + nums[right];
            
            if(sum == 0) {
                result.push_back({nums[i], nums[left], nums[right]});
                
                while(left < right && nums[left] == nums[left + 1]) left++;
                while(left < right && nums[right] == nums[right - 1]) right--;
                
                left++;
                right--;
            } else if(sum < 0) {
                left++;
            } else {
                right--;
            }
        }
    }
    
    return result;
}

// ===== PROBLEM 13: LONGEST SUBSTRING WITHOUT REPEATING CHARACTERS =====
int lengthOfLongestSubstring(string s) {
    unordered_map<char, int> charIndex;
    int maxLen = 0;
    int start = 0;
    
    for(int i = 0; i < s.length(); i++) {
        if(charIndex.find(s[i]) != charIndex.end() && charIndex[s[i]] >= start) {
            start = charIndex[s[i]] + 1;
        }
        
        charIndex[s[i]] = i;
        maxLen = max(maxLen, i - start + 1);
    }
    
    return maxLen;
}

// ===== PROBLEM 14: GROUP ANAGRAMS =====
vector<vector<string>> groupAnagrams(vector<string>& strs) {
    unordered_map<string, vector<string>> groups;
    
    for(string& s : strs) {
        string key = s;
        sort(key.begin(), key.end());
        groups[key].push_back(s);
    }
    
    vector<vector<string>> result;
    for(auto& pair : groups) {
        result.push_back(pair.second);
    }
    
    return result;
}

// ===== PROBLEM 15: TOP K FREQUENT ELEMENTS =====
vector<int> topKFrequent(vector<int>& nums, int k) {
    unordered_map<int, int> freq;
    for(int num : nums) {
        freq[num]++;
    }
    
    priority_queue<pair<int, int>> pq;
    for(auto& pair : freq) {
        pq.push({pair.second, pair.first});
    }
    
    vector<int> result;
    for(int i = 0; i < k; i++) {
        result.push_back(pq.top().second);
        pq.pop();
    }
    
    return result;
}

// ===== MAIN FUNCTION =====
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    // Test your solutions here
    
    return 0;
}


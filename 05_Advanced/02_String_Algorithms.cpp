/*
 * ZCO PREPARATION - ADVANCED: String Algorithms
 * 
 * KMP, Z-algorithm, rolling hash, string matching
 * Important for string processing problems
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
using namespace std;

// ===== 1. KMP ALGORITHM (Knuth-Morris-Pratt) =====
// Pattern matching in O(n + m) time

// Build prefix function (LPS array)
vector<int> buildLPS(string pattern) {
    int m = pattern.length();
    vector<int> lps(m, 0);
    int len = 0;
    int i = 1;
    
    while(i < m) {
        if(pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if(len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    
    return lps;
}

// KMP search - returns all occurrences
vector<int> KMPSearch(string text, string pattern) {
    vector<int> result;
    int n = text.length();
    int m = pattern.length();
    
    vector<int> lps = buildLPS(pattern);
    
    int i = 0;  // Index for text
    int j = 0;  // Index for pattern
    
    while(i < n) {
        if(pattern[j] == text[i]) {
            i++;
            j++;
        }
        
        if(j == m) {
            result.push_back(i - j);  // Pattern found at index i - j
            j = lps[j - 1];
        } else if(i < n && pattern[j] != text[i]) {
            if(j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }
    
    return result;
}

// ===== 2. Z-ALGORITHM =====
// Find all occurrences of pattern in text

vector<int> buildZArray(string s) {
    int n = s.length();
    vector<int> z(n, 0);
    int l = 0, r = 0;
    
    for(int i = 1; i < n; i++) {
        if(i <= r) {
            z[i] = min(r - i + 1, z[i - l]);
        }
        
        while(i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        
        if(i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    
    return z;
}

vector<int> ZSearch(string text, string pattern) {
    string combined = pattern + "$" + text;
    vector<int> z = buildZArray(combined);
    vector<int> result;
    
    int m = pattern.length();
    for(int i = m + 1; i < combined.length(); i++) {
        if(z[i] == m) {
            result.push_back(i - m - 1);
        }
    }
    
    return result;
}

// ===== 3. ROLLING HASH (Rabin-Karp) =====
// String matching using hash - average O(n + m)

const int BASE = 256;
const int MOD1 = 1000000007;
const int MOD2 = 1000000009;

long long modPow(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while(exp > 0) {
        if(exp & 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

long long computeHash(string s, long long mod, long long base) {
    long long hash = 0;
    for(char c : s) {
        hash = (hash * base + c) % mod;
    }
    return hash;
}

vector<int> rabinKarp(string text, string pattern) {
    vector<int> result;
    int n = text.length();
    int m = pattern.length();
    
    if(m > n) return result;
    
    long long patternHash1 = computeHash(pattern, MOD1, BASE);
    long long patternHash2 = computeHash(pattern, MOD2, BASE);
    
    long long textHash1 = 0, textHash2 = 0;
    long long power1 = modPow(BASE, m - 1, MOD1);
    long long power2 = modPow(BASE, m - 1, MOD2);
    
    // Compute hash of first window
    for(int i = 0; i < m; i++) {
        textHash1 = (textHash1 * BASE + text[i]) % MOD1;
        textHash2 = (textHash2 * BASE + text[i]) % MOD2;
    }
    
    // Check first window
    if(textHash1 == patternHash1 && textHash2 == patternHash2) {
        if(text.substr(0, m) == pattern) {
            result.push_back(0);
        }
    }
    
    // Slide window
    for(int i = m; i < n; i++) {
        // Remove leftmost character, add rightmost
        textHash1 = ((textHash1 - text[i - m] * power1) % MOD1 + MOD1) % MOD1;
        textHash1 = (textHash1 * BASE + text[i]) % MOD1;
        
        textHash2 = ((textHash2 - text[i - m] * power2) % MOD2 + MOD2) % MOD2;
        textHash2 = (textHash2 * BASE + text[i]) % MOD2;
        
        if(textHash1 == patternHash1 && textHash2 == patternHash2) {
            // Verify to handle hash collisions
            if(text.substr(i - m + 1, m) == pattern) {
                result.push_back(i - m + 1);
            }
        }
    }
    
    return result;
}

// ===== 4. LONGEST PALINDROMIC SUBSTRING =====
// Manacher's Algorithm - O(n)

string longestPalindromicSubstring(string s) {
    // Transform string: "abc" -> "^#a#b#c#$"
    string transformed = "^";
    for(char c : s) {
        transformed += "#";
        transformed += c;
    }
    transformed += "#$";
    
    int n = transformed.length();
    vector<int> p(n, 0);
    int center = 0, right = 0;
    
    for(int i = 1; i < n - 1; i++) {
        int mirror = 2 * center - i;
        
        if(i < right) {
            p[i] = min(right - i, p[mirror]);
        }
        
        // Expand around center
        while(transformed[i + (1 + p[i])] == transformed[i - (1 + p[i])]) {
            p[i]++;
        }
        
        // Update center and right
        if(i + p[i] > right) {
            center = i;
            right = i + p[i];
        }
    }
    
    // Find maximum
    int maxLen = 0, centerIdx = 0;
    for(int i = 1; i < n - 1; i++) {
        if(p[i] > maxLen) {
            maxLen = p[i];
            centerIdx = i;
        }
    }
    
    int start = (centerIdx - maxLen) / 2;
    return s.substr(start, maxLen);
}

// ===== 5. SUFFIX ARRAY (SIMPLIFIED) =====
// O(n log^2 n) implementation

struct Suffix {
    int index;
    string suffix;
};

vector<int> buildSuffixArray(string s) {
    int n = s.length();
    vector<Suffix> suffixes(n);
    
    for(int i = 0; i < n; i++) {
        suffixes[i].index = i;
        suffixes[i].suffix = s.substr(i);
    }
    
    sort(suffixes.begin(), suffixes.end(),
         [](const Suffix &a, const Suffix &b) {
             return a.suffix < b.suffix;
         });
    
    vector<int> suffixArray(n);
    for(int i = 0; i < n; i++) {
        suffixArray[i] = suffixes[i].index;
    }
    
    return suffixArray;
}

// ===== 6. LONGEST COMMON PREFIX ARRAY =====
vector<int> buildLCP(string s, vector<int> &suffixArray) {
    int n = s.length();
    vector<int> lcp(n, 0);
    vector<int> rank(n);
    
    for(int i = 0; i < n; i++) {
        rank[suffixArray[i]] = i;
    }
    
    int k = 0;
    for(int i = 0; i < n; i++) {
        if(rank[i] == n - 1) {
            k = 0;
            continue;
        }
        
        int j = suffixArray[rank[i] + 1];
        while(i + k < n && j + k < n && s[i + k] == s[j + k]) {
            k++;
        }
        
        lcp[rank[i]] = k;
        if(k > 0) k--;
    }
    
    return lcp;
}

// ===== 7. LONGEST REPEATING SUBSTRING =====
string longestRepeatingSubstring(string s) {
    vector<int> suffixArray = buildSuffixArray(s);
    vector<int> lcp = buildLCP(s, suffixArray);
    
    int maxLen = 0, start = 0;
    for(int i = 0; i < lcp.size(); i++) {
        if(lcp[i] > maxLen) {
            maxLen = lcp[i];
            start = suffixArray[i];
        }
    }
    
    return s.substr(start, maxLen);
}

// ===== 8. MINIMUM ROTATION (LEXICOGRAPHICALLY SMALLEST) =====
int minRotation(string s) {
    int n = s.length();
    s += s;  // Double the string
    int i = 0, ans = 0;
    
    while(i < n) {
        ans = i;
        int j = i + 1, k = i;
        
        while(j < 2 * n && s[k] <= s[j]) {
            if(s[k] < s[j]) {
                k = i;
            } else {
                k++;
            }
            j++;
        }
        
        while(i <= k) {
            i += j - k;
        }
    }
    
    return ans;
}

// ===== 9. ANAGRAM GROUPING =====
vector<vector<string>> groupAnagrams(vector<string> &strs) {
    map<string, vector<string>> groups;
    
    for(string &s : strs) {
        string key = s;
        sort(key.begin(), key.end());
        groups[key].push_back(s);
    }
    
    vector<vector<string>> result;
    for(auto &pair : groups) {
        result.push_back(pair.second);
    }
    
    return result;
}

// ===== 10. LONGEST COMMON SUBSTRING =====
string longestCommonSubstring(string s1, string s2) {
    int m = s1.length(), n = s2.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    
    int maxLen = 0, endIndex = 0;
    
    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            if(s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if(dp[i][j] > maxLen) {
                    maxLen = dp[i][j];
                    endIndex = i - 1;
                }
            }
        }
    }
    
    return s1.substr(endIndex - maxLen + 1, maxLen);
}

// ===== MAIN FUNCTION =====
int main() {
    string text = "ABABDABACDABABCABC";
    string pattern = "ABABCABC";
    
    cout << "Text: " << text << endl;
    cout << "Pattern: " << pattern << endl;
    
    // KMP Search
    vector<int> kmpResult = KMPSearch(text, pattern);
    cout << "KMP occurrences: ";
    for(int pos : kmpResult) cout << pos << " ";
    cout << endl;
    
    // Rabin-Karp
    vector<int> rkResult = rabinKarp(text, pattern);
    cout << "Rabin-Karp occurrences: ";
    for(int pos : rkResult) cout << pos << " ";
    cout << endl;
    
    // Longest Palindromic Substring
    string palindrome = "babad";
    cout << "\nLongest palindromic substring of '" << palindrome << "': ";
    cout << longestPalindromicSubstring(palindrome) << endl;
    
    return 0;
}


/*
 * ZCO PREPARATION - DATA STRUCTURES: Strings
 * 
 * String manipulation and common operations
 * Essential for string-based problems
 */

#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <cctype>
using namespace std;

int main() {
    // ===== STRING DECLARATION =====
    
    string s1;              // Empty string
    string s2 = "Hello";    // Initialize with value
    string s3("World");     // Constructor
    string s4(s2);          // Copy constructor
    string s5(5, 'a');      // 5 copies of 'a': "aaaaa"
    string s6(s2, 0, 3);    // Substring: "Hel" (from index 0, length 3)
    
    // ===== STRING OPERATIONS =====
    
    string str = "Hello";
    
    // Length
    cout << "Length: " << str.length() << endl;  // or str.size()
    
    // Access characters
    char ch = str[0];      // Direct access: 'H'
    char ch2 = str.at(0);  // With bounds check: 'H'
    
    // Modify characters
    str[0] = 'h';  // "hello"
    
    // Concatenation
    string s = "Hello" + string(" ") + "World";
    str += " ZCO";  // Append
    
    // Comparison
    string a = "abc", b = "def";
    if(a == b) cout << "Equal" << endl;
    if(a < b) cout << "a comes before b" << endl;
    if(a.compare(b) < 0) cout << "a comes before b" << endl;
    
    // ===== SUBSTRING =====
    
    string text = "Hello World";
    
    // substr(start, length)
    string sub1 = text.substr(0, 5);  // "Hello"
    string sub2 = text.substr(6);     // "World" (from index 6 to end)
    
    // ===== FIND OPERATIONS =====
    
    string haystack = "Hello World Hello";
    
    // Find first occurrence
    size_t pos = haystack.find("World");  // Returns index or string::npos
    if(pos != string::npos) {
        cout << "Found at index: " << pos << endl;
    }
    
    // Find last occurrence
    pos = haystack.rfind("Hello");
    
    // Find first of any character in set
    pos = haystack.find_first_of("aeiou");  // First vowel
    
    // Find first not of
    pos = haystack.find_first_not_of("H");
    
    // ===== REPLACE =====
    
    string rep = "Hello World";
    rep.replace(6, 5, "ZCO");  // Replace 5 chars starting at 6: "Hello ZCO"
    
    // Replace all occurrences (manual)
    string text2 = "apple apple apple";
    size_t found = 0;
    while((found = text2.find("apple", found)) != string::npos) {
        text2.replace(found, 5, "orange");
        found += 6;  // Move past replacement
    }
    
    // ===== INSERT AND ERASE =====
    
    string ins = "Hello";
    ins.insert(5, " World");  // "Hello World"
    ins.erase(5, 6);          // Remove 6 chars from index 5: "Hello"
    
    // ===== ITERATION =====
    
    string iter = "Hello";
    
    // Index-based
    for(int i = 0; i < iter.length(); i++) {
        cout << iter[i];
    }
    cout << endl;
    
    // Range-based for loop
    for(char c : iter) {
        cout << c;
    }
    cout << endl;
    
    // Iterator
    for(auto it = iter.begin(); it != iter.end(); it++) {
        cout << *it;
    }
    cout << endl;
    
    // ===== TRANSFORMATIONS =====
    
    string trans = "Hello World";
    
    // Convert to uppercase
    transform(trans.begin(), trans.end(), trans.begin(), ::toupper);
    cout << trans << endl;  // "HELLO WORLD"
    
    // Convert to lowercase
    transform(trans.begin(), trans.end(), trans.begin(), ::tolower);
    cout << trans << endl;  // "hello world"
    
    // ===== CHARACTER CHECKS (from <cctype>) =====
    
    char c = 'A';
    isalpha(c);   // Is alphabetic
    isdigit(c);   // Is digit
    isalnum(c);   // Is alphanumeric
    isspace(c);   // Is whitespace
    isupper(c);   // Is uppercase
    islower(c);   // Is lowercase
    
    toupper(c);   // Convert to uppercase
    tolower(c);   // Convert to lowercase
    
    // ===== STRING TO NUMBER =====
    
    // String to integer
    string numStr = "12345";
    int num = stoi(numStr);        // String to int
    long long numLL = stoll(numStr);  // String to long long
    
    // Number to string
    int number = 12345;
    string strNum = to_string(number);
    
    // Using stringstream (more flexible)
    stringstream ss;
    ss << 12345;
    string result = ss.str();
    
    // ===== STRING TOKENIZATION (SPLIT) =====
    
    // Method 1: Using stringstream
    string input = "Hello World ZCO";
    stringstream ss2(input);
    string token;
    vector<string> tokens;
    
    while(ss2 >> token) {
        tokens.push_back(token);
    }
    // tokens = {"Hello", "World", "ZCO"}
    
    // Method 2: Manual split by delimiter
    string input2 = "apple,orange,banana";
    string delimiter = ",";
    vector<string> tokens2;
    size_t pos2 = 0;
    string token2;
    
    while((pos2 = input2.find(delimiter)) != string::npos) {
        token2 = input2.substr(0, pos2);
        tokens2.push_back(token2);
        input2.erase(0, pos2 + delimiter.length());
    }
    tokens2.push_back(input2);  // Last token
    
    // ===== SORTING STRING =====
    
    string sortStr = "dcba";
    sort(sortStr.begin(), sortStr.end());  // "abcd"
    
    // Sort in descending order
    sort(sortStr.begin(), sortStr.end(), greater<char>());
    
    // ===== REVERSE STRING =====
    
    string rev = "Hello";
    reverse(rev.begin(), rev.end());  // "olleH"
    
    // ===== CHECK PALINDROME =====
    
    bool isPalindrome(string s) {
        int left = 0, right = s.length() - 1;
        while(left < right) {
            if(s[left] != s[right]) return false;
            left++;
            right--;
        }
        return true;
    }
    
    // Or simply:
    string pal = "racecar";
    string palRev = pal;
    reverse(palRev.begin(), palRev.end());
    bool isPal = (pal == palRev);
    
    // ===== COMMON PATTERNS FOR CP =====
    
    // 1. Character frequency
    string freqStr = "hello";
    int freq[26] = {0};  // For lowercase letters
    
    for(char c : freqStr) {
        freq[c - 'a']++;
    }
    
    // 2. String matching (naive)
    bool containsSubstring(string text, string pattern) {
        return text.find(pattern) != string::npos;
    }
    
    // 3. Remove duplicates
    string removeDup = "aabbcc";
    string result2 = "";
    for(char c : removeDup) {
        if(result2.empty() || result2.back() != c) {
            result2 += c;
        }
    }
    
    // 4. String rotation
    string rotate = "abcd";
    rotate(rotate.begin(), rotate.begin() + 1, rotate.end());  // Left rotate by 1: "bcda"
    
    // 5. Check anagram
    bool areAnagrams(string s1, string s2) {
        sort(s1.begin(), s1.end());
        sort(s2.begin(), s2.end());
        return s1 == s2;
    }
    
    // 6. Longest Common Prefix
    string longestCommonPrefix(vector<string>& strs) {
        if(strs.empty()) return "";
        
        string prefix = strs[0];
        for(int i = 1; i < strs.size(); i++) {
            while(strs[i].find(prefix) != 0) {
                prefix = prefix.substr(0, prefix.length() - 1);
                if(prefix.empty()) return "";
            }
        }
        return prefix;
    }
    
    // ===== PERFORMANCE TIPS =====
    
    // 1. Use string concatenation carefully
    // Bad (O(n^2)):
    // string result = "";
    // for(int i = 0; i < n; i++) result += "a";
    
    // Good (O(n)):
    // string result(n, 'a');
    
    // 2. Prefer string functions over manual loops when possible
    // 3. Use reserve() if you know approximate size
    string res;
    res.reserve(1000);
    
    return 0;
}


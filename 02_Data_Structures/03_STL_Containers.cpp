/*
 * ZCO PREPARATION - DATA STRUCTURES: STL Containers
 * 
 * Standard Template Library containers
 * Essential for efficient competitive programming
 */

#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <stack>
#include <queue>
#include <priority_queue>
#include <algorithm>
using namespace std;

int main() {
    // ===== PAIR =====
    // Stores two values together
    
    pair<int, int> p1 = {1, 2};
    pair<int, string> p2 = make_pair(3, "Hello");
    
    cout << p1.first << " " << p1.second << endl;
    
    // Nested pairs
    pair<pair<int, int>, int> p3 = {{1, 2}, 3};
    
    // ===== VECTOR (Already covered, but here for completeness) =====
    vector<int> v = {1, 2, 3, 4, 5};
    
    // ===== DEQUE (Double-ended queue) =====
    // Similar to vector but efficient insertion/deletion at both ends
    
    deque<int> dq;
    dq.push_back(1);   // Add to end - O(1)
    dq.push_front(2);  // Add to front - O(1)
    dq.pop_back();     // Remove from end - O(1)
    dq.pop_front();    // Remove from front - O(1)
    
    // Access
    dq[0];        // Random access
    dq.front();   // First element
    dq.back();    // Last element
    
    // ===== LIST (Doubly linked list) =====
    // Efficient insertion/deletion anywhere
    
    list<int> lst;
    lst.push_back(1);
    lst.push_front(2);
    lst.insert(lst.begin(), 0);  // Insert at position
    
    // No random access, use iterators
    for(auto it = lst.begin(); it != lst.end(); it++) {
        cout << *it << " ";
    }
    
    // ===== SET (Ordered, unique elements) =====
    // Automatically sorted, no duplicates - O(log n) operations
    
    set<int> s;
    s.insert(3);  // O(log n)
    s.insert(1);
    s.insert(2);
    s.insert(3);  // Duplicate, ignored
    
    // Check if element exists
    if(s.find(2) != s.end()) {
        cout << "Found" << endl;
    }
    
    // Count (0 or 1 for set)
    if(s.count(2)) {
        cout << "Exists" << endl;
    }
    
    // Iterate (sorted order)
    for(int x : s) {
        cout << x << " ";  // 1 2 3
    }
    
    // Lower bound (first element >= value)
    auto lb = s.lower_bound(2);
    
    // Upper bound (first element > value)
    auto ub = s.upper_bound(2);
    
    // Erase
    s.erase(2);        // Erase by value
    s.erase(s.begin()); // Erase by iterator
    
    // ===== MULTISET (Ordered, allows duplicates) =====
    multiset<int> ms;
    ms.insert(1);
    ms.insert(1);
    ms.insert(2);
    // ms = {1, 1, 2}
    
    // Count occurrences
    int count = ms.count(1);  // 2
    
    // ===== UNORDERED_SET (Hash set) =====
    // Average O(1) operations, no ordering
    
    unordered_set<int> us;
    us.insert(3);
    us.insert(1);
    us.insert(2);
    
    // Check membership
    if(us.find(2) != us.end()) {
        cout << "Found" << endl;
    }
    
    // ===== MAP (Ordered key-value pairs) =====
    // Key-value pairs, sorted by key - O(log n) operations
    
    map<string, int> mp;
    mp["apple"] = 5;
    mp["banana"] = 3;
    mp["orange"] = 7;
    
    // Check if key exists
    if(mp.find("apple") != mp.end()) {
        cout << mp["apple"] << endl;
    }
    
    // Count (0 or 1 for map)
    if(mp.count("apple")) {
        cout << "Key exists" << endl;
    }
    
    // Iterate (sorted by key)
    for(auto it = mp.begin(); it != mp.end(); it++) {
        cout << it->first << " " << it->second << endl;
    }
    
    // Range-based for loop
    for(auto &pair : mp) {
        cout << pair.first << " " << pair.second << endl;
    }
    
    // ===== MULTIMAP (Allows duplicate keys) =====
    multimap<string, int> mmp;
    
    // ===== UNORDERED_MAP (Hash map) =====
    // Average O(1) operations, no ordering
    
    unordered_map<string, int> ump;
    ump["apple"] = 5;
    ump["banana"] = 3;
    
    // Access
    cout << ump["apple"] << endl;
    
    // ===== STACK (LIFO - Last In First Out) =====
    
    stack<int> st;
    st.push(1);   // Add to top - O(1)
    st.push(2);
    st.push(3);
    
    st.top();     // View top element - O(1)
    st.pop();     // Remove top - O(1)
    st.empty();   // Check if empty
    st.size();    // Get size
    
    // ===== QUEUE (FIFO - First In First Out) =====
    
    queue<int> q;
    q.push(1);    // Add to back - O(1)
    q.push(2);
    q.push(3);
    
    q.front();    // View front - O(1)
    q.back();     // View back - O(1)
    q.pop();      // Remove front - O(1)
    q.empty();
    q.size();
    
    // ===== PRIORITY_QUEUE (Heap) =====
    // Always gives max/min element - O(log n) insert/remove
    
    // Max heap (default)
    priority_queue<int> pq;
    pq.push(3);   // Insert - O(log n)
    pq.push(1);
    pq.push(5);
    
    pq.top();     // View max - O(1): 5
    pq.pop();     // Remove max - O(log n)
    
    // Min heap
    priority_queue<int, vector<int>, greater<int>> min_pq;
    min_pq.push(3);
    min_pq.push(1);
    min_pq.push(5);
    
    min_pq.top();  // Min: 1
    
    // Custom comparator
    auto cmp = [](int a, int b) { return a > b; };
    priority_queue<int, vector<int>, decltype(cmp)> custom_pq(cmp);
    
    // ===== COMMON PATTERNS FOR CP =====
    
    // 1. Frequency counting with map
    vector<int> arr = {1, 2, 2, 3, 3, 3};
    map<int, int> freq;
    
    for(int x : arr) {
        freq[x]++;
    }
    
    // 2. Get unique elements (using set)
    vector<int> withDup = {3, 1, 2, 2, 3, 1};
    set<int> uniqueSet(withDup.begin(), withDup.end());
    vector<int> uniqueVec(uniqueSet.begin(), uniqueSet.end());
    
    // 3. Sliding window with deque (for max/min in window)
    vector<int> window = {1, 3, -1, -3, 5, 3, 6, 7};
    int k = 3;  // Window size
    deque<int> dq2;
    vector<int> result;
    
    for(int i = 0; i < window.size(); i++) {
        // Remove indices outside window
        while(!dq2.empty() && dq2.front() <= i - k) {
            dq2.pop_front();
        }
        
        // Remove smaller elements from back
        while(!dq2.empty() && window[dq2.back()] < window[i]) {
            dq2.pop_back();
        }
        
        dq2.push_back(i);
        
        // Window of size k formed
        if(i >= k - 1) {
            result.push_back(window[dq2.front()]);
        }
    }
    
    // 4. Top K frequent elements
    vector<int> nums = {1, 1, 1, 2, 2, 3};
    int k2 = 2;
    
    map<int, int> frequency;
    for(int x : nums) frequency[x]++;
    
    priority_queue<pair<int, int>> pq2;  // {frequency, element}
    for(auto &p : frequency) {
        pq2.push({p.second, p.first});
    }
    
    vector<int> topK;
    for(int i = 0; i < k2 && !pq2.empty(); i++) {
        topK.push_back(pq2.top().second);
        pq2.pop();
    }
    
    // 5. Two Sum problem
    vector<int> twoSum = {2, 7, 11, 15};
    int target = 9;
    unordered_map<int, int> seen;  // {value, index}
    
    for(int i = 0; i < twoSum.size(); i++) {
        int complement = target - twoSum[i];
        if(seen.find(complement) != seen.end()) {
            // Found pair: seen[complement] and i
        }
        seen[twoSum[i]] = i;
    }
    
    // 6. Balanced parentheses using stack
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
    
    // ===== PERFORMANCE NOTES =====
    
    // 1. Use unordered_map/set when order doesn't matter (faster)
    // 2. Use map/set when you need sorted order
    // 3. Priority queue is efficient for finding max/min quickly
    // 4. Stack/Queue have O(1) operations
    
    return 0;
}


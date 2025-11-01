/*
 * ZCO PREPARATION - DATA STRUCTURES: Arrays and Vectors
 * 
 * Arrays, Vectors, and common operations
 * Most fundamental data structure in competitive programming
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <array>  // For std::array
using namespace std;

int main() {
    // ===== C-STYLE ARRAYS =====
    
    // Fixed size array
    int arr1[5] = {1, 2, 3, 4, 5};
    int arr2[] = {1, 2, 3};  // Size inferred
    
    // Access elements
    cout << "arr1[0] = " << arr1[0] << endl;
    
    // Size of array
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    
    // Variable length array (VLA) - available in some compilers
    int n = 10;
    int arr3[n];  // Be careful: size must be known at runtime
    
    // Initialize all elements to 0
    int arr4[10] = {0};  // All zeros
    
    // ===== VECTORS (PREFERRED IN CP) =====
    
    // Declaration methods
    vector<int> v1;                    // Empty vector
    vector<int> v2(5);                 // Size 5, all zeros
    vector<int> v3(5, 10);             // Size 5, all values 10
    vector<int> v4 = {1, 2, 3, 4, 5};  // Initialize with values
    vector<int> v5(v4);                // Copy constructor
    vector<int> v6(v4.begin(), v4.end());  // From iterators
    
    // ===== VECTOR OPERATIONS =====
    
    vector<int> v;
    
    // Add elements
    v.push_back(1);  // Add to end - O(1)
    v.push_back(2);
    v.push_back(3);
    
    // Insert element at position
    v.insert(v.begin() + 1, 99);  // Insert at index 1 - O(n)
    
    // Remove elements
    v.pop_back();  // Remove from end - O(1)
    v.erase(v.begin() + 1);  // Remove at index 1 - O(n)
    v.erase(v.begin(), v.begin() + 2);  // Remove range - O(n)
    
    // Access elements
    v[0] = 10;           // Direct access (no bounds check)
    v.at(0) = 20;        // With bounds check (throws exception)
    int first = v.front();  // First element
    int last = v.back();    // Last element
    
    // Size and capacity
    cout << "Size: " << v.size() << endl;
    cout << "Empty: " << v.empty() << endl;
    v.resize(10);        // Resize to 10
    v.reserve(100);      // Reserve capacity for 100 elements
    
    // Clear vector
    v.clear();  // Removes all elements
    
    // ===== ITERATION METHODS =====
    
    vector<int> nums = {1, 2, 3, 4, 5};
    
    // Method 1: Index-based
    for(int i = 0; i < nums.size(); i++) {
        cout << nums[i] << " ";
    }
    cout << endl;
    
    // Method 2: Range-based for loop (C++11)
    for(int x : nums) {
        cout << x << " ";
    }
    cout << endl;
    
    // Method 3: Iterators
    for(auto it = nums.begin(); it != nums.end(); it++) {
        cout << *it << " ";
    }
    cout << endl;
    
    // Method 4: Reverse iteration
    for(auto it = nums.rbegin(); it != nums.rend(); it++) {
        cout << *it << " ";
    }
    cout << endl;
    
    // ===== 2D VECTORS (MATRICES) =====
    
    // Declaration
    vector<vector<int>> matrix1;  // Empty 2D vector
    vector<vector<int>> matrix2(3, vector<int>(4));  // 3x4, all zeros
    vector<vector<int>> matrix3(3, vector<int>(4, 5)); // 3x4, all values 5
    
    // Initialize with values
    vector<vector<int>> matrix4 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    
    // Access and modify
    matrix4[0][0] = 10;
    cout << "matrix4[1][2] = " << matrix4[1][2] << endl;
    
    // Iterate 2D vector
    for(int i = 0; i < matrix4.size(); i++) {
        for(int j = 0; j < matrix4[i].size(); j++) {
            cout << matrix4[i][j] << " ";
        }
        cout << endl;
    }
    
    // ===== COMMON ALGORITHMS WITH VECTORS =====
    
    vector<int> arr = {3, 1, 4, 1, 5, 9, 2, 6};
    
    // Sort
    sort(arr.begin(), arr.end());  // Ascending - O(n log n)
    sort(arr.begin(), arr.end(), greater<int>());  // Descending
    
    // Reverse
    reverse(arr.begin(), arr.end());
    
    // Find element
    auto it = find(arr.begin(), arr.end(), 5);
    if(it != arr.end()) {
        cout << "Found at position: " << (it - arr.begin()) << endl;
    }
    
    // Count occurrences
    int count = count(arr.begin(), arr.end(), 1);
    
    // Maximum and minimum
    int max_val = *max_element(arr.begin(), arr.end());
    int min_val = *min_element(arr.begin(), arr.end());
    
    // Sum of elements
    int sum = 0;
    for(int x : arr) sum += x;
    // OR use accumulate: #include <numeric>
    
    // Binary search (requires sorted array)
    bool found = binary_search(arr.begin(), arr.end(), 5);
    
    // Lower bound (first element >= value)
    auto lb = lower_bound(arr.begin(), arr.end(), 5);
    
    // Upper bound (first element > value)
    auto ub = upper_bound(arr.begin(), arr.end(), 5);
    
    // Unique elements (removes consecutive duplicates, requires sorted)
    vector<int> dup = {1, 1, 2, 2, 3, 3};
    auto last = unique(dup.begin(), dup.end());
    dup.erase(last, dup.end());
    
    // ===== PRACTICAL PATTERNS FOR CP =====
    
    // 1. Sliding Window
    vector<int> window = {1, 2, 3, 4, 5, 6, 7, 8};
    int k = 3;  // Window size
    int windowSum = 0;
    
    // Calculate sum of first window
    for(int i = 0; i < k; i++) {
        windowSum += window[i];
    }
    
    // Slide the window
    for(int i = k; i < window.size(); i++) {
        windowSum = windowSum - window[i - k] + window[i];
        // Process windowSum
    }
    
    // 2. Prefix Sum
    vector<int> prefix = {1, 2, 3, 4, 5};
    vector<long long> prefixSum(prefix.size());
    prefixSum[0] = prefix[0];
    
    for(int i = 1; i < prefix.size(); i++) {
        prefixSum[i] = prefixSum[i - 1] + prefix[i];
    }
    
    // Query sum from l to r: prefixSum[r] - prefixSum[l-1]
    
    // 3. Two Pointers Technique
    vector<int> sorted = {1, 2, 3, 4, 5, 6, 7, 8};
    int target = 10;
    int left = 0, right = sorted.size() - 1;
    
    while(left < right) {
        int sum = sorted[left] + sorted[right];
        if(sum == target) {
            // Found pair
            break;
        } else if(sum < target) {
            left++;
        } else {
            right--;
        }
    }
    
    // 4. Kadane's Algorithm (Maximum Subarray Sum)
    vector<int> kadane = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int maxSum = kadane[0];
    int currentSum = kadane[0];
    
    for(int i = 1; i < kadane.size(); i++) {
        currentSum = max(kadane[i], currentSum + kadane[i]);
        maxSum = max(maxSum, currentSum);
    }
    cout << "Maximum subarray sum: " << maxSum << endl;
    
    // ===== PERFORMANCE TIPS =====
    
    // 1. Use reserve() when you know the size to avoid reallocation
    vector<int> vec;
    vec.reserve(1000000);  // Reserve space
    
    // 2. Prefer vectors over arrays for dynamic sizing
    // 3. Use emplace_back() instead of push_back() for objects (faster)
    // 4. Be careful with insert() and erase() - they are O(n)
    
    return 0;
}


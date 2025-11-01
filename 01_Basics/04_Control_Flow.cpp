/*
 * ZCO PREPARATION - BASICS: Control Flow (if, loops, switch)
 * 
 * Decision making and iteration in C++
 */

#include <iostream>
#include <vector>
using namespace std;

int main() {
    // ===== IF-ELSE STATEMENTS =====
    
    int score = 85;
    
    if(score >= 90) {
        cout << "Grade A" << endl;
    } else if(score >= 80) {
        cout << "Grade B" << endl;
    } else if(score >= 70) {
        cout << "Grade C" << endl;
    } else {
        cout << "Grade D" << endl;
    }
    
    // Nested if-else
    int x = 10, y = 20;
    if(x > 0) {
        if(y > 0) {
            cout << "Both positive" << endl;
        }
    }
    
    // ===== SWITCH STATEMENT =====
    
    int choice = 2;
    switch(choice) {
        case 1:
            cout << "Option 1 selected" << endl;
            break;  // IMPORTANT: Don't forget break!
        case 2:
            cout << "Option 2 selected" << endl;
            break;
        case 3:
            cout << "Option 3 selected" << endl;
            break;
        default:
            cout << "Invalid option" << endl;
    }
    
    // ===== FOR LOOP =====
    
    // Basic for loop
    for(int i = 0; i < 5; i++) {
        cout << i << " ";
    }
    cout << endl;
    
    // Loop with multiple variables
    for(int i = 0, j = 10; i < 5; i++, j--) {
        cout << i << "," << j << " ";
    }
    cout << endl;
    
    // Reverse loop
    for(int i = 4; i >= 0; i--) {
        cout << i << " ";
    }
    cout << endl;
    
    // ===== WHILE LOOP =====
    
    int count = 0;
    while(count < 5) {
        cout << count << " ";
        count++;
    }
    cout << endl;
    
    // Infinite loop (use with break)
    int num = 0;
    while(true) {
        num++;
        if(num == 10) break;  // Exit loop
        cout << num << " ";
    }
    cout << endl;
    
    // ===== DO-WHILE LOOP =====
    // Executes at least once (checks condition after first iteration)
    
    int val = 10;
    do {
        cout << val << " ";
        val++;
    } while(val < 5);  // Still executes once even though condition is false
    
    // ===== RANGE-BASED FOR LOOP (C++11) =====
    
    vector<int> arr = {1, 2, 3, 4, 5};
    
    // Iterate by value (copies elements)
    for(int element : arr) {
        cout << element << " ";
    }
    cout << endl;
    
    // Iterate by reference (no copy, can modify)
    for(int &element : arr) {
        element *= 2;  // Modify original array
    }
    
    // Iterate with auto (C++11)
    for(auto element : arr) {
        cout << element << " ";
    }
    cout << endl;
    
    // ===== BREAK AND CONTINUE =====
    
    // break: Exit the innermost loop
    for(int i = 0; i < 10; i++) {
        if(i == 5) break;  // Exit loop at i=5
        cout << i << " ";
    }
    cout << endl;
    
    // continue: Skip to next iteration
    for(int i = 0; i < 10; i++) {
        if(i % 2 == 0) continue;  // Skip even numbers
        cout << i << " ";  // Only prints odd numbers
    }
    cout << endl;
    
    // ===== NESTED LOOPS =====
    
    // Print pattern
    int n = 5;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= i; j++) {
            cout << "* ";
        }
        cout << endl;
    }
    
    // Common pattern: Iterate through 2D array
    vector<vector<int>> grid = {{1,2,3}, {4,5,6}, {7,8,9}};
    for(int i = 0; i < grid.size(); i++) {
        for(int j = 0; j < grid[i].size(); j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
    
    // ===== PRACTICAL EXAMPLES FOR CP =====
    
    // 1. Find first occurrence
    vector<int> nums = {3, 1, 4, 1, 5, 9, 2};
    int target = 1;
    int firstIndex = -1;
    
    for(int i = 0; i < nums.size(); i++) {
        if(nums[i] == target) {
            firstIndex = i;
            break;  // Stop at first occurrence
        }
    }
    
    // 2. Count occurrences
    int countTarget = 0;
    for(int num : nums) {
        if(num == target) countTarget++;
    }
    
    // 3. Find maximum element
    int maxElement = nums[0];
    for(int num : nums) {
        if(num > maxElement) {
            maxElement = num;
        }
    }
    
    // 4. Two pointers technique (important algorithm)
    vector<int> sortedArr = {1, 2, 3, 4, 5, 6};
    int targetSum = 7;
    
    int left = 0, right = sortedArr.size() - 1;
    bool found = false;
    
    while(left < right) {
        int sum = sortedArr[left] + sortedArr[right];
        if(sum == targetSum) {
            found = true;
            break;
        } else if(sum < targetSum) {
            left++;
        } else {
            right--;
        }
    }
    
    return 0;
}


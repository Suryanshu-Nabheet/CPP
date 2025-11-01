/*
 * ZCO PREPARATION - BASICS: Input/Output
 * 
 * This file covers fundamental input/output operations in C++
 * Essential for all competitive programming problems
 */

#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    // ===== SINGLE INTEGER INPUT/OUTPUT =====
    int n;
    cin >> n;  // Read a single integer
    cout << n << endl;  // Print with newline
    
    // ===== MULTIPLE VALUES =====
    int a, b, c;
    cin >> a >> b >> c;  // Read multiple values in one line
    cout << a << " " << b << " " << c << endl;
    
    // ===== STRING INPUT =====
    string s;
    cin >> s;  // Reads until whitespace
    cout << s << endl;
    
    // For reading entire line (including spaces)
    string line;
    getline(cin, line);  // Read complete line
    // Note: If cin was used before, use cin.ignore() to skip newline
    cin.ignore();
    getline(cin, line);
    cout << line << endl;
    
    // ===== ARRAY INPUT/OUTPUT =====
    int size;
    cin >> size;
    int arr[size];  // Variable length array (C-style)
    
    // Read array elements
    for(int i = 0; i < size; i++) {
        cin >> arr[i];
    }
    
    // Print array elements
    for(int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    // ===== VECTOR INPUT/OUTPUT (PREFERRED) =====
    int n;
    cin >> n;
    vector<int> v(n);  // Vector of size n
    
    // Read vector
    for(int i = 0; i < n; i++) {
        cin >> v[i];
    }
    
    // Print vector (method 1)
    for(int i = 0; i < n; i++) {
        cout << v[i] << " ";
    }
    cout << endl;
    
    // Print vector (method 2 - range-based loop)
    for(int x : v) {
        cout << x << " ";
    }
    cout << endl;
    
    // ===== 2D ARRAY/GRID INPUT =====
    int rows, cols;
    cin >> rows >> cols;
    
    vector<vector<int>> grid(rows, vector<int>(cols));
    
    // Read 2D grid
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            cin >> grid[i][j];
        }
    }
    
    // Print 2D grid
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
    
    // ===== FAST I/O (FOR COMPETITIVE PROGRAMMING) =====
    // Add these lines at the start of main() for faster I/O
    ios_base::sync_with_stdio(false);  // Disable synchronization with C I/O
    cin.tie(NULL);  // Untie cin from cout (faster)
    
    // After this, don't use printf/scanf, only cin/cout
    
    return 0;
}


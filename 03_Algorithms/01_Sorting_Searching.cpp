/*
 * ZCO PREPARATION - ALGORITHMS: Sorting and Searching
 * 
 * Essential sorting and searching algorithms
 * Critical for competitive programming
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

// ===== SORTING ALGORITHMS =====

// 1. Bubble Sort - O(n^2)
void bubbleSort(vector<int> &arr) {
    int n = arr.size();
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// 2. Selection Sort - O(n^2)
void selectionSort(vector<int> &arr) {
    int n = arr.size();
    for(int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for(int j = i + 1; j < n; j++) {
            if(arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        swap(arr[i], arr[minIdx]);
    }
}

// 3. Insertion Sort - O(n^2), good for small arrays
void insertionSort(vector<int> &arr) {
    int n = arr.size();
    for(int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while(j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// 4. Merge Sort - O(n log n), stable
void merge(vector<int> &arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    vector<int> L(n1), R(n2);
    for(int i = 0; i < n1; i++) L[i] = arr[left + i];
    for(int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    while(i < n1 && j < n2) {
        if(L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }
    
    while(i < n1) arr[k++] = L[i++];
    while(j < n2) arr[k++] = R[j++];
}

void mergeSort(vector<int> &arr, int left, int right) {
    if(left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// 5. Quick Sort - O(n log n) average, O(n^2) worst
int partition(vector<int> &arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    
    for(int j = low; j < high; j++) {
        if(arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int> &arr, int low, int high) {
    if(low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// ===== STL SORT (MOST IMPORTANT FOR CP) =====
// Use this in competitive programming - highly optimized
void stlSortExample() {
    vector<int> arr = {3, 1, 4, 1, 5, 9, 2, 6};
    
    // Ascending order
    sort(arr.begin(), arr.end());
    
    // Descending order
    sort(arr.begin(), arr.end(), greater<int>());
    
    // Custom comparator
    sort(arr.begin(), arr.end(), [](int a, int b) {
        return a > b;
    });
    
    // Sort only part of array
    sort(arr.begin(), arr.begin() + 4);
}

// ===== SEARCHING ALGORITHMS =====

// 1. Linear Search - O(n)
int linearSearch(vector<int> &arr, int target) {
    for(int i = 0; i < arr.size(); i++) {
        if(arr[i] == target) {
            return i;
        }
    }
    return -1;
}

// 2. Binary Search - O(log n) - REQUIRES SORTED ARRAY
int binarySearch(vector<int> &arr, int target) {
    int left = 0, right = arr.size() - 1;
    
    while(left <= right) {
        int mid = left + (right - left) / 2;  // Avoid overflow
        
        if(arr[mid] == target) {
            return mid;
        } else if(arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;  // Not found
}

// Binary Search - Lower Bound (first element >= target)
int lowerBound(vector<int> &arr, int target) {
    int left = 0, right = arr.size();
    
    while(left < right) {
        int mid = left + (right - left) / 2;
        if(arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left;
}

// Binary Search - Upper Bound (first element > target)
int upperBound(vector<int> &arr, int target) {
    int left = 0, right = arr.size();
    
    while(left < right) {
        int mid = left + (right - left) / 2;
        if(arr[mid] <= target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left;
}

// STL Binary Search
void stlBinarySearch() {
    vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    
    // binary_search: returns true/false
    bool found = binary_search(arr.begin(), arr.end(), 5);
    
    // lower_bound: returns iterator to first element >= target
    auto lb = lower_bound(arr.begin(), arr.end(), 5);
    int index = lb - arr.begin();
    
    // upper_bound: returns iterator to first element > target
    auto ub = upper_bound(arr.begin(), arr.end(), 5);
    
    // Count elements equal to target
    int count = ub - lb;
}

// 3. Ternary Search - O(log3 n) for unimodal functions
int ternarySearch(vector<int> &arr, int target) {
    int left = 0, right = arr.size() - 1;
    
    while(left <= right) {
        int mid1 = left + (right - left) / 3;
        int mid2 = right - (right - left) / 3;
        
        if(arr[mid1] == target) return mid1;
        if(arr[mid2] == target) return mid2;
        
        if(target < arr[mid1]) {
            right = mid1 - 1;
        } else if(target > arr[mid2]) {
            left = mid2 + 1;
        } else {
            left = mid1 + 1;
            right = mid2 - 1;
        }
    }
    return -1;
}

// ===== APPLICATIONS =====

// Find floor of target (largest element <= target)
int floorSearch(vector<int> &arr, int target) {
    int left = 0, right = arr.size() - 1;
    int result = -1;
    
    while(left <= right) {
        int mid = left + (right - left) / 2;
        if(arr[mid] <= target) {
            result = arr[mid];
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return result;
}

// Find ceiling of target (smallest element >= target)
int ceilingSearch(vector<int> &arr, int target) {
    int left = 0, right = arr.size() - 1;
    int result = -1;
    
    while(left <= right) {
        int mid = left + (right - left) / 2;
        if(arr[mid] >= target) {
            result = arr[mid];
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return result;
}

// Binary search on answer (important technique)
// Example: Find square root of n
double sqrtBinarySearch(int n) {
    double left = 0, right = n;
    double precision = 1e-6;
    
    while(right - left > precision) {
        double mid = left + (right - left) / 2;
        if(mid * mid <= n) {
            left = mid;
        } else {
            right = mid;
        }
    }
    return left;
}

// Find peak element (element greater than neighbors)
int findPeak(vector<int> &arr) {
    int left = 0, right = arr.size() - 1;
    
    while(left < right) {
        int mid = left + (right - left) / 2;
        if(arr[mid] < arr[mid + 1]) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left;
}

// Rotated sorted array search
int searchRotated(vector<int> &arr, int target) {
    int left = 0, right = arr.size() - 1;
    
    while(left <= right) {
        int mid = left + (right - left) / 2;
        
        if(arr[mid] == target) return mid;
        
        // Left half is sorted
        if(arr[left] <= arr[mid]) {
            if(target >= arr[left] && target < arr[mid]) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        // Right half is sorted
        else {
            if(target > arr[mid] && target <= arr[right]) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }
    return -1;
}

// ===== MAIN FUNCTION =====
int main() {
    vector<int> arr = {64, 34, 25, 12, 22, 11, 90};
    
    // Using STL sort (preferred)
    vector<int> arr2 = arr;
    sort(arr2.begin(), arr2.end());
    
    cout << "Sorted array: ";
    for(int x : arr2) cout << x << " ";
    cout << endl;
    
    // Binary search
    vector<int> sorted = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int index = binarySearch(sorted, 5);
    cout << "Found 5 at index: " << index << endl;
    
    // Lower and upper bound
    vector<int> arr3 = {1, 2, 2, 2, 3, 4, 5};
    int lb = lowerBound(arr3, 2);
    int ub = upperBound(arr3, 2);
    cout << "Lower bound of 2: " << lb << endl;
    cout << "Upper bound of 2: " << ub << endl;
    cout << "Count of 2: " << (ub - lb) << endl;
    
    return 0;
}


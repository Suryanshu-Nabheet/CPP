/*
 * ZCO PREPARATION - BASICS: Functions
 * 
 * Function declaration, definition, and various types
 * Essential for code organization and reusability
 */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// ===== FUNCTION PROTOTYPES =====
// Declare functions before main() if defined after
int add(int a, int b);
void printArray(vector<int> arr);

// ===== BASIC FUNCTION =====
int add(int a, int b) {
    return a + b;
}

// ===== VOID FUNCTION (NO RETURN) =====
void greet(string name) {
    cout << "Hello, " << name << "!" << endl;
}

// ===== FUNCTION WITH DEFAULT PARAMETERS =====
int multiply(int a, int b = 1) {
    return a * b;
}

// ===== PASS BY VALUE (COPY) =====
void incrementByValue(int x) {
    x++;  // Only modifies copy, original unchanged
}

// ===== PASS BY REFERENCE (MODIFIES ORIGINAL) =====
void incrementByReference(int &x) {
    x++;  // Modifies original variable
}

// ===== PASS BY POINTER =====
void incrementByPointer(int *x) {
    (*x)++;  // Dereference and increment
}

// ===== RETURN BY VALUE =====
int getSquare(int n) {
    return n * n;
}

// ===== RETURN BY REFERENCE (USE WITH CAUTION) =====
int& getElement(vector<int> &arr, int index) {
    return arr[index];  // Returns reference to element
}

// ===== CONST PARAMETERS =====
void printConst(const vector<int> &arr) {
    // arr cannot be modified inside this function
    // Pass by const reference to avoid copy but prevent modification
    for(int x : arr) {
        cout << x << " ";
    }
    cout << endl;
}

// ===== RECURSIVE FUNCTION =====
int factorial(int n) {
    // Base case
    if(n <= 1) {
        return 1;
    }
    // Recursive case
    return n * factorial(n - 1);
}

// ===== FIBONACCI (RECURSIVE - SLOW) =====
int fibonacci(int n) {
    if(n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// ===== FIBONACCI (ITERATIVE - FAST) =====
int fibonacciFast(int n) {
    if(n <= 1) return n;
    
    int prev = 0, curr = 1;
    for(int i = 2; i <= n; i++) {
        int next = prev + curr;
        prev = curr;
        curr = next;
    }
    return curr;
}

// ===== FUNCTION OVERLOADING =====
// Multiple functions with same name but different parameters
int max(int a, int b) {
    return (a > b) ? a : b;
}

double max(double a, double b) {
    return (a > b) ? a : b;
}

int max(int a, int b, int c) {
    return max(max(a, b), c);
}

// ===== TEMPLATE FUNCTION (GENERIC) =====
template <typename T>
T maximum(T a, T b) {
    return (a > b) ? a : b;
}

// Template with multiple types
template <typename T, typename U>
auto addDifferent(T a, U b) -> decltype(a + b) {
    return a + b;
}

// ===== INLINE FUNCTION =====
// Suggests compiler to inline the function (avoid function call overhead)
inline int square(int x) {
    return x * x;
}

// ===== LAMBDA FUNCTION (C++11) =====
// Anonymous function, useful for algorithms
void lambdaExample() {
    vector<int> nums = {3, 1, 4, 1, 5, 9};
    
    // Lambda: [capture](parameters) -> return_type { body }
    auto isEven = [](int x) -> bool {
        return x % 2 == 0;
    };
    
    // Use lambda with algorithm
    auto it = find_if(nums.begin(), nums.end(), isEven);
    
    // Lambda with capture
    int threshold = 5;
    auto isGreater = [threshold](int x) {
        return x > threshold;
    };
    
    // Capture all by reference
    int sum = 0;
    for_each(nums.begin(), nums.end(), [&sum](int x) {
        sum += x;
    });
}

// ===== PRACTICAL EXAMPLES FOR CP =====

// Binary Search
bool binarySearch(vector<int> &arr, int target) {
    int left = 0, right = arr.size() - 1;
    
    while(left <= right) {
        int mid = left + (right - left) / 2;  // Avoid overflow
        if(arr[mid] == target) {
            return true;
        } else if(arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return false;
}

// Greatest Common Divisor (GCD) - Euclidean Algorithm
int gcd(int a, int b) {
    if(b == 0) return a;
    return gcd(b, a % b);
}

// Least Common Multiple (LCM)
int lcm(int a, int b) {
    return (a / gcd(a, b)) * b;
}

// Power with modulo (for large numbers)
long long power(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    
    while(exp > 0) {
        if(exp & 1) {  // If exp is odd
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp >>= 1;  // Divide exp by 2
    }
    
    return result;
}

// Check if number is prime
bool isPrime(int n) {
    if(n < 2) return false;
    if(n == 2) return true;
    if(n % 2 == 0) return false;
    
    for(int i = 3; i * i <= n; i += 2) {
        if(n % i == 0) return false;
    }
    return true;
}

// ===== MAIN FUNCTION =====
int main() {
    // Basic function call
    int result = add(5, 3);
    cout << "5 + 3 = " << result << endl;
    
    // Void function
    greet("ZCO Contestant");
    
    // Default parameter
    cout << "5 * 1 = " << multiply(5) << endl;
    cout << "5 * 3 = " << multiply(5, 3) << endl;
    
    // Pass by value vs reference
    int num = 10;
    incrementByValue(num);
    cout << "After pass by value: " << num << endl;  // Still 10
    
    incrementByReference(num);
    cout << "After pass by reference: " << num << endl;  // Now 11
    
    // Recursive function
    cout << "Factorial of 5: " << factorial(5) << endl;
    
    // Function overloading
    cout << "max(3, 5) = " << max(3, 5) << endl;
    cout << "max(3.5, 2.1) = " << max(3.5, 2.1) << endl;
    cout << "max(3, 5, 7) = " << max(3, 5, 7) << endl;
    
    // Template function
    cout << "maximum(10, 20) = " << maximum(10, 20) << endl;
    cout << "maximum(3.14, 2.71) = " << maximum(3.14, 2.71) << endl;
    
    // Binary search
    vector<int> sorted = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    cout << "Binary search for 5: " << (binarySearch(sorted, 5) ? "Found" : "Not found") << endl;
    
    // GCD and LCM
    cout << "GCD(48, 18) = " << gcd(48, 18) << endl;
    cout << "LCM(48, 18) = " << lcm(48, 18) << endl;
    
    return 0;
}


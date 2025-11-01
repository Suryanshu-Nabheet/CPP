/*
 * ZCO PREPARATION - BASICS: Data Types and Variables
 * 
 * Understanding different data types and their ranges
 * Critical for avoiding overflow and TLE issues
 */

#include <iostream>
#include <climits>  // For limits of data types
#include <cmath>
using namespace std;

int main() {
    // ===== INTEGER TYPES =====
    
    // int: -2^31 to 2^31 - 1 (approximately -2*10^9 to 2*10^9)
    int a = 42;
    cout << "int size: " << sizeof(int) << " bytes" << endl;
    cout << "int range: " << INT_MIN << " to " << INT_MAX << endl;
    
    // long long: -2^63 to 2^63 - 1 (approximately -9*10^18 to 9*10^18)
    // ALWAYS use long long for competitive programming to avoid overflow
    long long big_num = 1000000000000LL;  // Note the LL suffix
    cout << "long long size: " << sizeof(long long) << " bytes" << endl;
    
    // unsigned: Only positive numbers (0 to 2^32 - 1 for int)
    unsigned int pos_only = 100;
    
    // ===== FLOATING POINT TYPES =====
    
    // float: Single precision (6-7 decimal digits)
    float f = 3.14f;  // Note the 'f' suffix
    
    // double: Double precision (15-17 decimal digits) - PREFERRED
    double d = 3.141592653589793;
    
    // long double: Extended precision
    long double ld = 3.141592653589793238L;
    
    // ===== CHARACTER TYPES =====
    char c = 'A';
    cout << "Character: " << c << ", ASCII: " << (int)c << endl;
    
    // String: Array of characters
    string str = "Hello ZCO!";
    cout << "String: " << str << ", Length: " << str.length() << endl;
    
    // ===== BOOLEAN =====
    bool flag = true;  // true = 1, false = 0
    cout << "Boolean: " << flag << endl;
    
    // ===== TYPE MODIFIERS =====
    
    // const: Value cannot be changed
    const int MAX_N = 100000;
    // MAX_N = 50;  // ERROR: Cannot modify const
    
    // ===== TYPE CASTING =====
    
    // Implicit casting
    int x = 5;
    double y = x;  // int to double (automatic)
    
    // Explicit casting
    double z = 5.7;
    int w = (int)z;  // C-style cast (cuts off decimal)
    int w2 = static_cast<int>(z);  // C++ style (preferred)
    
    // ===== IMPORTANT NOTES FOR COMPETITIVE PROGRAMMING =====
    
    // 1. Use long long when:
    //    - Numbers can exceed 10^9
    //    - Multiplying two large integers
    //    - Array indices might be very large
    
    long long product = (long long)1000000 * 1000000;  // Correct way
    
    // 2. Be careful with floating point precision
    //    Avoid direct equality checks
    double num1 = 0.1 + 0.2;
    double num2 = 0.3;
    
    // WRONG: if(num1 == num2)
    // CORRECT: Use epsilon for comparison
    double epsilon = 1e-9;
    if(abs(num1 - num2) < epsilon) {
        cout << "Numbers are approximately equal" << endl;
    }
    
    // 3. Use appropriate data types for memory efficiency
    //    - Use int for small arrays
    //    - Use long long when needed
    //    - Use bool for boolean arrays (1 byte vs 4 bytes for int)
    
    return 0;
}


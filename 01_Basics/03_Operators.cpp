/*
 * ZCO PREPARATION - BASICS: Operators
 * 
 * All types of operators in C++ and their usage
 */

#include <iostream>
using namespace std;

int main() {
    // ===== ARITHMETIC OPERATORS =====
    int a = 10, b = 3;
    
    cout << "a + b = " << (a + b) << endl;  // Addition: 13
    cout << "a - b = " << (a - b) << endl;  // Subtraction: 7
    cout << "a * b = " << (a * b) << endl;  // Multiplication: 30
    cout << "a / b = " << (a / b) << endl;  // Division: 3 (integer division)
    cout << "a % b = " << (a % b) << endl;  // Modulo: 1 (remainder)
    
    // Integer division truncates (cuts off decimal)
    // For floating point division, use floating point types
    double result = (double)a / b;  // 3.333...
    
    // ===== MODULO OPERATOR (IMPORTANT FOR CP) =====
    // Used frequently in competitive programming:
    // - Check even/odd: n % 2
    // - Circular arrays: (i + 1) % n
    // - Modular arithmetic: (a + b) % mod
    
    // ===== INCREMENT/DECREMENT =====
    int x = 5;
    x++;  // Post-increment: x = 6 (returns old value)
    ++x;  // Pre-increment: x = 7 (returns new value)
    
    x--;  // Post-decrement
    --x;  // Pre-decrement
    
    // Difference between post and pre:
    int y = 5;
    int z = y++;  // z = 5, y = 6
    int w = ++y;  // w = 7, y = 7
    
    // ===== ASSIGNMENT OPERATORS =====
    int num = 10;
    num += 5;  // num = num + 5
    num -= 3;  // num = num - 3
    num *= 2;  // num = num * 2
    num /= 4;  // num = num / 4
    num %= 3;  // num = num % 3
    
    // ===== RELATIONAL OPERATORS =====
    int p = 10, q = 20;
    
    cout << (p == q) << endl;  // Equal: false (0)
    cout << (p != q) << endl;  // Not equal: true (1)
    cout << (p < q) << endl;   // Less than: true
    cout << (p > q) << endl;   // Greater than: false
    cout << (p <= q) << endl;  // Less than or equal: true
    cout << (p >= q) << endl;  // Greater than or equal: false
    
    // ===== LOGICAL OPERATORS =====
    bool condition1 = true, condition2 = false;
    
    cout << (condition1 && condition2) << endl;  // AND: false (both must be true)
    cout << (condition1 || condition2) << endl;  // OR: true (either can be true)
    cout << (!condition1) << endl;               // NOT: false (flips value)
    
    // ===== BITWISE OPERATORS (ADVANCED - VERY USEFUL IN CP) =====
    int bit1 = 5;   // Binary: 101
    int bit2 = 3;   // Binary: 011
    
    cout << (bit1 & bit2) << endl;  // AND: 001 = 1 (both bits 1)
    cout << (bit1 | bit2) << endl;  // OR: 111 = 7 (either bit 1)
    cout << (bit1 ^ bit2) << endl;  // XOR: 110 = 6 (different bits)
    cout << (~bit1) << endl;        // NOT: Inverts all bits
    cout << (bit1 << 1) << endl;    // Left shift: 1010 = 10 (multiply by 2)
    cout << (bit1 >> 1) << endl;    // Right shift: 10 = 2 (divide by 2)
    
    // Bitwise tricks for competitive programming:
    
    // 1. Check if number is power of 2
    int n = 16;
    bool isPowerOf2 = (n & (n - 1)) == 0;  // true for powers of 2
    
    // 2. Count set bits (number of 1s in binary)
    int count = 0;
    while(n) {
        count += (n & 1);  // Check if last bit is 1
        n >>= 1;            // Right shift
    }
    // OR use built-in: __builtin_popcount(n)
    
    // 3. Get the lowest set bit
    int lsb = n & (-n);  // Gets the rightmost set bit
    
    // 4. Set bit at position i
    int num = 5, pos = 2;  // Binary: 101
    num |= (1 << pos);     // Set bit 2: 111 = 7
    
    // 5. Clear bit at position i
    num &= ~(1 << pos);    // Clear bit 2: 101 = 5
    
    // 6. Toggle bit at position i
    num ^= (1 << pos);     // Toggle bit 2
    
    // 7. Check if bit i is set
    bool isSet = (num >> pos) & 1;
    
    // ===== TERNARY OPERATOR =====
    int max_val = (a > b) ? a : b;  // If a > b return a, else return b
    
    // Equivalent to:
    // int max_val;
    // if(a > b) max_val = a;
    // else max_val = b;
    
    // ===== OPERATOR PRECEDENCE =====
    // Arithmetic > Relational > Logical
    // Use parentheses when in doubt!
    
    int result2 = 2 + 3 * 4;      // 14 (multiplication first)
    int result3 = (2 + 3) * 4;    // 20 (parentheses first)
    
    return 0;
}


/*
 * ZCO PREPARATION - ADVANCED: Number Theory
 * 
 * Prime numbers, GCD, LCM, modular arithmetic
 * Essential for mathematical problems
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <bitset>
using namespace std;

// ===== 1. PRIME NUMBERS =====

// Check if number is prime - O(sqrt(n))
bool isPrime(int n) {
    if(n < 2) return false;
    if(n == 2) return true;
    if(n % 2 == 0) return false;
    
    for(int i = 3; i * i <= n; i += 2) {
        if(n % i == 0) return false;
    }
    
    return true;
}

// Sieve of Eratosthenes - Find all primes up to n
// Time: O(n log log n)
vector<bool> sieveOfEratosthenes(int n) {
    vector<bool> isPrime(n + 1, true);
    isPrime[0] = isPrime[1] = false;
    
    for(int i = 2; i * i <= n; i++) {
        if(isPrime[i]) {
            for(int j = i * i; j <= n; j += i) {
                isPrime[j] = false;
            }
        }
    }
    
    return isPrime;
}

// Get list of primes up to n
vector<int> getPrimes(int n) {
    vector<bool> sieve = sieveOfEratosthenes(n);
    vector<int> primes;
    
    for(int i = 2; i <= n; i++) {
        if(sieve[i]) {
            primes.push_back(i);
        }
    }
    
    return primes;
}

// Prime factorization
vector<pair<int, int>> primeFactors(int n) {
    vector<pair<int, int>> factors;
    
    for(int i = 2; i * i <= n; i++) {
        if(n % i == 0) {
            int count = 0;
            while(n % i == 0) {
                count++;
                n /= i;
            }
            factors.push_back({i, count});
        }
    }
    
    if(n > 1) {
        factors.push_back({n, 1});
    }
    
    return factors;
}

// Count divisors
int countDivisors(int n) {
    vector<pair<int, int>> factors = primeFactors(n);
    int count = 1;
    
    for(auto &factor : factors) {
        count *= (factor.second + 1);
    }
    
    return count;
}

// Sum of divisors
long long sumOfDivisors(int n) {
    vector<pair<int, int>> factors = primeFactors(n);
    long long sum = 1;
    
    for(auto &factor : factors) {
        long long term = 1;
        for(int i = 1; i <= factor.second; i++) {
            term = term * factor.first + 1;
        }
        sum *= term;
    }
    
    return sum;
}

// ===== 2. GCD AND LCM =====

// Euclidean Algorithm - O(log min(a, b))
int gcd(int a, int b) {
    if(b == 0) return a;
    return gcd(b, a % b);
}

// Iterative GCD
int gcdIterative(int a, int b) {
    while(b) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Built-in: __gcd(a, b)

// LCM
long long lcm(int a, int b) {
    return (long long)a / gcd(a, b) * b;
}

// Extended Euclidean Algorithm
// Returns gcd and finds x, y such that ax + by = gcd(a, b)
int extendedGcd(int a, int b, int &x, int &y) {
    if(b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    
    int x1, y1;
    int g = extendedGcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    
    return g;
}

// ===== 3. MODULAR ARITHMETIC =====

const int MOD = 1000000007;  // Common mod in CP

// Modular addition
int modAdd(int a, int b, int mod = MOD) {
    return ((long long)a + b) % mod;
}

// Modular subtraction
int modSub(int a, int b, int mod = MOD) {
    return ((a - b) % mod + mod) % mod;
}

// Modular multiplication
int modMul(int a, int b, int mod = MOD) {
    return ((long long)a * b) % mod;
}

// Modular exponentiation - O(log n)
long long modPow(long long base, long long exp, long long mod = MOD) {
    long long result = 1;
    base %= mod;
    
    while(exp > 0) {
        if(exp & 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp >>= 1;
    }
    
    return result;
}

// Modular division (using modular inverse)
// For prime mod, use Fermat's Little Theorem: a^(-1) = a^(mod-2) mod mod
long long modInverse(long long a, long long mod = MOD) {
    return modPow(a, mod - 2, mod);
}

long long modDiv(long long a, long long b, long long mod = MOD) {
    return (a * modInverse(b, mod)) % mod;
}

// ===== 4. FACTORIAL AND COMBINATIONS =====

// Factorial
long long factorial(int n, long long mod = MOD) {
    long long fact = 1;
    for(int i = 2; i <= n; i++) {
        fact = (fact * i) % mod;
    }
    return fact;
}

// Precompute factorials (for multiple queries)
vector<long long> precomputeFactorials(int n, long long mod = MOD) {
    vector<long long> fact(n + 1);
    fact[0] = fact[1] = 1;
    
    for(int i = 2; i <= n; i++) {
        fact[i] = (fact[i - 1] * i) % mod;
    }
    
    return fact;
}

// nCr (Combination) - O(n)
long long nCr(int n, int r, long long mod = MOD) {
    if(r > n || r < 0) return 0;
    if(r == 0 || r == n) return 1;
    
    if(r > n - r) r = n - r;  // Use symmetry
    
    long long result = 1;
    for(int i = 0; i < r; i++) {
        result = (result * (n - i)) % mod;
        result = (result * modInverse(i + 1, mod)) % mod;
    }
    
    return result;
}

// nCr using precomputed factorials - O(1) per query
long long nCrFast(int n, int r, vector<long long> &fact, long long mod = MOD) {
    if(r > n || r < 0) return 0;
    long long numerator = fact[n];
    long long denominator = (fact[r] * fact[n - r]) % mod;
    return (numerator * modInverse(denominator, mod)) % mod;
}

// nPr (Permutation)
long long nPr(int n, int r, long long mod = MOD) {
    if(r > n || r < 0) return 0;
    
    long long result = 1;
    for(int i = 0; i < r; i++) {
        result = (result * (n - i)) % mod;
    }
    
    return result;
}

// ===== 5. CHINESE REMAINDER THEOREM =====
// Solve system: x ≡ a1 (mod m1), x ≡ a2 (mod m2), ...

// ===== 6. EULER'S TOTIENT FUNCTION =====
// Count numbers <= n coprime with n

int eulerTotient(int n) {
    int result = n;
    
    for(int i = 2; i * i <= n; i++) {
        if(n % i == 0) {
            while(n % i == 0) {
                n /= i;
            }
            result -= result / i;
        }
    }
    
    if(n > 1) {
        result -= result / n;
    }
    
    return result;
}

// Totient for all numbers up to n (using sieve)
vector<int> eulerTotientSieve(int n) {
    vector<int> phi(n + 1);
    for(int i = 0; i <= n; i++) {
        phi[i] = i;
    }
    
    for(int i = 2; i <= n; i++) {
        if(phi[i] == i) {  // i is prime
            for(int j = i; j <= n; j += i) {
                phi[j] -= phi[j] / i;
            }
        }
    }
    
    return phi;
}

// ===== 7. FAST POWER (ALREADY COVERED) =====
// See modPow above

// ===== 8. LUCAS THEOREM =====
// For computing nCr mod p where p is prime

long long lucasNCR(int n, int r, int p) {
    if(r == 0) return 1;
    int ni = n % p, ri = r % p;
    if(ni < ri) return 0;
    return (nCr(ni, ri, p) * lucasNCR(n / p, r / p, p)) % p;
}

// ===== 9. CATALAN NUMBERS =====
// C(n) = (2n)! / ((n+1)! * n!)
// Sequence: 1, 1, 2, 5, 14, 42, 132, ...

long long catalan(int n, long long mod = MOD) {
    return modDiv(nCr(2 * n, n, mod), n + 1, mod);
}

// ===== 10. FIBONACCI WITH MATRIX EXPONENTIATION =====
// O(log n) to compute nth Fibonacci number

vector<vector<long long>> matrixMultiply(vector<vector<long long>> &a, 
                                          vector<vector<long long>> &b, 
                                          long long mod = MOD) {
    int n = a.size();
    vector<vector<long long>> result(n, vector<long long>(n, 0));
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            for(int k = 0; k < n; k++) {
                result[i][j] = (result[i][j] + a[i][k] * b[k][j]) % mod;
            }
        }
    }
    
    return result;
}

vector<vector<long long>> matrixPower(vector<vector<long long>> base, 
                                       long long exp, 
                                       long long mod = MOD) {
    int n = base.size();
    vector<vector<long long>> result(n, vector<long long>(n, 0));
    for(int i = 0; i < n; i++) result[i][i] = 1;  // Identity matrix
    
    while(exp > 0) {
        if(exp & 1) {
            result = matrixMultiply(result, base, mod);
        }
        base = matrixMultiply(base, base, mod);
        exp >>= 1;
    }
    
    return result;
}

long long fibonacci(long long n, long long mod = MOD) {
    if(n <= 1) return n;
    
    vector<vector<long long>> base = {{1, 1}, {1, 0}};
    vector<vector<long long>> result = matrixPower(base, n - 1, mod);
    
    return result[0][0];
}

// ===== MAIN FUNCTION =====
int main() {
    // Prime check
    cout << "Is 17 prime? " << isPrime(17) << endl;
    
    // Sieve
    vector<bool> primes = sieveOfEratosthenes(50);
    cout << "Primes up to 50: ";
    for(int i = 2; i <= 50; i++) {
        if(primes[i]) cout << i << " ";
    }
    cout << endl;
    
    // GCD and LCM
    cout << "GCD(48, 18) = " << gcd(48, 18) << endl;
    cout << "LCM(48, 18) = " << lcm(48, 18) << endl;
    
    // Prime factors
    vector<pair<int, int>> factors = primeFactors(60);
    cout << "Prime factors of 60: ";
    for(auto &f : factors) {
        cout << f.first << "^" << f.second << " ";
    }
    cout << endl;
    
    // Modular exponentiation
    cout << "2^10 mod 1000 = " << modPow(2, 10, 1000) << endl;
    
    // Combinations
    cout << "C(5, 2) = " << nCr(5, 2) << endl;
    
    // Euler Totient
    cout << "φ(10) = " << eulerTotient(10) << endl;
    
    // Fibonacci
    cout << "F(10) = " << fibonacci(10) << endl;
    
    return 0;
}


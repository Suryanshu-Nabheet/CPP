/*
 * ZCO COMPETITIVE PROGRAMMING TEMPLATE
 * 
 * Use this template for all ZCO problems
 * Includes common headers and fast I/O
 */

#include <bits/stdc++.h>
using namespace std;

// Fast I/O
#define ios ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

// Common macros
#define ll long long
#define vi vector<int>
#define vll vector<long long>
#define pii pair<int, int>
#define pll pair<long long, long long>
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define endl '\n'

// Loop macros
#define FOR(i, a, b) for(int i = (a); i < (b); i++)
#define FORR(i, a, b) for(int i = (a); i >= (b); i--)
#define REP(i, n) FOR(i, 0, n)
#define REPR(i, n) FORR(i, n - 1, 0)

// Debugging
#ifdef LOCAL
#define debug(x) cerr << #x << " = " << x << endl
#else
#define debug(x)
#endif

// Constants
const int MOD = 1000000007;
const int INF = INT_MAX;
const ll LINF = LLONG_MAX;

// GCD and LCM
ll gcd(ll a, ll b) {
    if(b == 0) return a;
    return gcd(b, a % b);
}

ll lcm(ll a, ll b) {
    return (a / gcd(a, b)) * b;
}

// Modular arithmetic
ll modAdd(ll a, ll b, ll mod = MOD) {
    return ((a % mod) + (b % mod)) % mod;
}

ll modSub(ll a, ll b, ll mod = MOD) {
    return ((a % mod) - (b % mod) + mod) % mod;
}

ll modMul(ll a, ll b, ll mod = MOD) {
    return ((a % mod) * (b % mod)) % mod;
}

ll modPow(ll base, ll exp, ll mod = MOD) {
    ll result = 1;
    base %= mod;
    while(exp > 0) {
        if(exp & 1) result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

ll modInverse(ll a, ll mod = MOD) {
    return modPow(a, mod - 2, mod);
}

// Main function
void solve() {
    // Your solution here
    
}

int main() {
    ios;
    
    int t = 1;
    // cin >> t;  // Uncomment for multiple test cases
    
    while(t--) {
        solve();
    }
    
    return 0;
}


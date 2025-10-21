#include <bits/stdc++.h>

using ll = long long;
using ld = long double;
using ull = unsigned long long int;

#define pi pair<int, int>
#define pl pair<ll, ll>
#define pd pair<ld, ld>

#define vi vector<int>
#define vl vector<ll>
#define vd vector<ld>
#define vpi vector<pi>
#define vpl vector<pl>
#define vpd vector<pd>

#define forf(i, m, n) for(int i = m; i <= (int)n; i++)
#define forb(i, m, n) for(int i = m; i >= (int)n; i--)

#define pb push_back
#define f first
#define s second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
#define lb lower_bound
#define up upper_bound

using namespace std;

inline int gcd(int a, int b) {
    for (; b > 0; a %= b, swap(a, b)) {}
    return a;
}

// end of template

template <typename T>
T modPow(T base, T exp, T modulus) {
  base %= modulus;
  T result = 1;
  while (exp > 0) {
    if (exp & 1) result = (result * base) % modulus;
    base = (base * base) % modulus;
    exp >>= 1;
  }
  return result;
}

template <typename T>
T modMul(T a, T b, T modulo) {
    return ((a % modulo) * (b % modulo)) % modulo;
}

template <typename T>
T modSum(T a, T b, T modulo) {
    return (a % modulo + b%modulo) % modulo;
}

/**
 * Rabin-karp algorithm implementation;
 * search for pattern in O(n+m-1) (avg)
 * 
 * @param T text
 * @param P pattern
 * @param d alphabet
 * @param q modulus
 *
 * @return index of first occurance or -1 if pattern is not present in text
 */
int rabin_karp(string T, string P, int d, int q) {
    int n = (int)T.size();
    int m = (int)P.size();
    int h = modPow(d, m-1, q);
    int p = 0;
    int t = 0;
    for (int i = 0; i < m; i++) {
        p = (d * p + P[i]) % q;
        t = (d * t + T[i]) % q;
    }
    for (int s = 0; s <= n-m; s++) {
        if (p==t) {
            if (T.substr(s, m) == P) {
                return s;
            }
        }
        if (s < n-m) {
            t = (d * (t - T[s] * h) + T[s+m]) % q;
            t = (t % q + q) % q;
        }
    }

    return -1;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    string s = "abracadabra";
    string t = "cad";

    cout << rabin_karp(s,t, 256, 100) << endl;
}

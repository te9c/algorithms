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

// Return index of element if found.
// Otherwise, return -1
int bisearch(vi a, int value) {
    int l = 0;
    int r = a.size() - 1;

    while (l <= r) {
        int m = l + (r- l) / 2;
        if (a[m] == value)
            return m;
        else if (a[m] > value)
            r = m-1;
        else
            l = m+1;
    }

    return -1;
}

// Return first element in a that is greater (>) than value
int upbnd(vi a, int value) {
    int l = 0;
    int r = a.size() - 1;

    while (l < r) {
        int m = l + (r - l) / 2;

        if (a[m] <= value)
            l = m+1;
        else
            r = m;
    }

    // if value is greater than the last element in a
    if (l < (int)a.size() && a[l] <= value)
        l++;

    return l;
}

// Return first element in a that is greater or equals (>=) than value
int lobnd(vi a, int value) {
    int l = 0;
    int r = a.size() - 1;

    while (l < r) {
        int m = l + (r-l)/2;

        if (a[m] >= value) {
            r = m;
        }
        else
            l = m + 1;
    }

    // if value is greater than last element in a
    if (l < (int)a.size() && a[l] < value)
        l++;

    return l;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    vi A = {12, 32, 64, 64, 64, 67};

    cout << upbnd(A, 64) << '\n';
}

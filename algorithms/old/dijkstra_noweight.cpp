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

vector<vi> g;
int n;

vi dijkstra(int root) {
    int dest[n];
    forf (i, 0, n-1) {
        dest[i] = INT_MAX;
    }
    deque<int> dq;
    dq.push()
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    n = 5;
    g = {
        {1},
        {0,2},
        {1,3,4},
        {2},
        {2}
    };
}

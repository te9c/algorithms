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

int n = 6;
vector<vpi> g; // first - node, second - price

vi dijkstra(int root) {
    vi dist(n, INT_MAX);
    dist[root] = 0;
    vi checked(n, 0);
    priority_queue<pi, vpi, greater<pi>> pq;
    pq.push({dist[root], root});

    while (sz(pq)) {
        int current = pq.top().s;
        pq.pop();
        if (checked[current])
            continue;
        checked[current] = true;

        for (auto neig : g[current]) {
            dist[neig.f] = min(dist[neig.f], dist[current] + neig.s);
            pq.push({dist[neig.f], neig.f});
        }
    }

    return dist;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    g.resize(n);
    // example on https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm
    g = {
        { {1, 7}, {2, 9}, {5, 14} },
        { {0, 7}, {2, 10}, {3, 15} },
        { {0, 9}, {1, 10}, {3, 11}, {5, 2} },
        { {1, 15}, {2, 11}, {4, 6}},
        { {3, 6}, {5, 9}},
        { {0, 14}, {2,2}, {4,9}},
    };
    vi dist = dijkstra(0);
    cout << "distances from node 0:\n";
    forf (i, 0, n-1) {
        cout << "to " << i + 1 << ": " << dist[i] << endl;
    }
}

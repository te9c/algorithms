#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define MAX_N 100

const ll inf = INTMAX_MAX;

ll f[MAX_N][MAX_N], c[MAX_N][MAX_N];
ll d[MAX_N], p[MAX_N];
ll s,t,n;
bool bfs() {
    for (ll i = 0; i < n; ++i) {
        d[i] = inf;
    }
    d[s] = 0;
    queue<ll> q;
    q.push(s);
    while (q.size()) {
        ll u = q.front();
        q.pop();
        for (ll i = 0; i < n; ++i) {
            if (f[u][i] < c[u][i] && d[i] == inf) {
                d[i] = d[u] + 1;
                q.push(i);
            }
        }
    }
    return d[t] != inf;
}

ll dfs(ll u, ll minC) {
    if (u == t || minC == 0) {
        return minC;
    }

    for (ll v = p[u]; v < n; ++v) {
        if (d[v] == d[u] + 1) {
            ll delta = dfs(v, min(minC, c[u][v] - f[u][v]));
            if (delta != 0) {
                f[u][v] += delta;
                f[v][u] -= delta;
                return delta;
            }
        }
        p[u]++;
    }
    return 0;
}

ll dinic() {
    ll max_flow = 0;
    while (bfs()) {
        memset(p, 0, n * sizeof(ll));
        ll flow = dfs(s, inf);
        while (flow != 0) {
            max_flow += flow;
            flow = dfs(s, inf);
        }
    }
    return max_flow;
}

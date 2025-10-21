#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int n, logn;
vector<vector<int>> g;
vector<int> tin,tout;
vector<vector<int>> up;
int timer = 0;

void init(int _n) {
    n = _n;
    logn = __lg(n) + 1;
    g.assign(n, vector<int>());
    tin.assign(n, 0);
    tout.assign(n, 0);
    up.assign(n, vector<int>(logn, 0));
}

void dfs(int node, int parent = -1) {
    tin[node] = timer++;
    for (int i = 1; i < logn; ++i) {
        up[node][i] = up[up[node][i-1]][i-1];
    }
    for (auto child : g[node]) {
        if (child == parent)
            continue;
        up[child][0] = node;
        dfs(child, node);
    }
    tout[node] = timer++;
}

bool is_ancestor(int u, int v) {
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int a, int b) {
    if (is_ancestor(a, b)) return a;
    if (is_ancestor(b, a)) return b;
    for (int i = logn - 1; i >= 0; --i) {
        if (!is_ancestor(up[a][i], b))
            a = up[a][i];
    }
    return up[a][0];
}

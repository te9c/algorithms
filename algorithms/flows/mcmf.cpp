#include <bits/stdc++.h>

using namespace std;
using ll = long long;


// Works for both directed, undirected and with negative cost too
// doesn't work for negative cycles
// for undirected edges just make the directed flag false
// Complexity: O(min(E^2 *V log V, E logV * flow))
using T = long long;
const T inf = 1LL << 61;
struct MCMF {
  struct Edge {
    int from, to;
    T cap, cost;
    Edge(int _from, int _to, T _cap, T _cost) {
      from = _from;
      to = _to;
      cap = _cap;
      cost = _cost;
    }
  };
  int n, s, t;
  T flow, min_cost;
  vector<vector<int>> g;
  vector<Edge> e;
  vector<T> d, potential;
  vector<int> par;
  bool neg;
  MCMF() {}
  MCMF(int _n) { // 0-based indexing
    n = _n + 10;
    g.assign(n, vector<int>());
    neg = false;
  }
  void add_edge(int u, int v, T cap, T cost, bool directed = true) {
    if (cost < 0)
      neg = true;
    g[u].emplace_back((int)e.size());
    e.emplace_back(u, v, cap, cost);
    g[v].emplace_back((int)e.size());
    e.emplace_back(v, u, 0, -cost);
    if (!directed)
      add_edge(v, u, cap, cost, true);
  }
  bool dijkstra() {
    par.assign(n, -1);
    d.assign(n, inf);
    // we have access to largest element by default, so we use greater
    priority_queue<pair<T, T>, vector<pair<T, T>>, greater<pair<T, T>>> q;
    d[s] = 0;
    q.emplace(0, s); // dist, v
    while (!q.empty()) {
      int from = q.top().second;
      T nw = q.top().first;
      q.pop();
      if (nw != d[from])
        continue;
      for (int id : g[from]) {
        int to = e[id].to;
        T cap = e[id].cap;
        T w = e[id].cost + potential[from] - potential[to];
        if (d[from] + w < d[to] && cap > 0) {
          d[to] = d[from] + w;
          par[to] = id;
          q.emplace(d[to], to);
        }
      }
    }
    for (int i = 0; i < n; i++) {
      if (d[i] < inf)
        d[i] += (potential[i] - potential[s]);
    }
    for (int i = 0; i < n; i++) {
      if (d[i] < inf)
        potential[i] = d[i];
    }
    return d[t] != inf; // for max flow min cost
    // return d[t] <= 0; // for min cost flow
  }
  T send_flow(int v, T cur) {
    if (par[v] == -1)
      return cur;
    int id = par[v];
    int from = e[id].from;
    T w = e[id].cost;
    T f = send_flow(from, min(cur, e[id].cap));
    min_cost += f * w;
    e[id].cap -= f;
    e[id ^ 1].cap += f;
    return f;
  }
  // returns {maxflow, mincost}
  pair<T, T> solve(int _s, int _t, T goal = inf) {
    s = _s;
    t = _t;
    flow = 0, min_cost = 0;
    potential.assign(n, 0);
    if (neg) {
      // Run Bellman-Ford to find starting potential on the starting graph
      // If the starting graph (before pushing flow in the residual graph) is a
      // DAG, then this can be calculated in O(V + E) using DP: potential(v) =
      // min({potential[u] + cost[u][v]}) for each u -> v and potential[s] = 0
      d.assign(n, inf);
      d[s] = 0;
      bool relax = true;
      for (int i = 0; i < n && relax; i++) {
        relax = false;
        for (int from = 0; from < n; from++) {
          for (int id : g[from]) {
            int v = e[id].to;
            T cap = e[id].cap, w = e[id].cost;
            if (d[v] > d[from] + w && cap > 0) {
              d[v] = d[from] + w;
              relax = true;
            }
          }
        }
      }
      for (int i = 0; i < n; i++)
        if (d[i] < inf)
          potential[i] = d[i];
    }
    while (flow < goal && dijkstra())
      flow += send_flow(t, goal - flow);
    return {flow, min_cost};
  }
};

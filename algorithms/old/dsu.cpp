#include <bits/stdc++.h>

using namespace std;

vector<int> p,h;

int get(int u)
{
    
    while (p[u] != -1) {
        u = p[u];
    }
    return u;
};
void unite(int u, int v) {
    int a = get(u);
    int b = get(v);
    if (a == b) {
        return;
    }
    int h1 = h[a];
    int h2 = h[b];
    if (h1 <= h2) {
        p[v] = u;
        h[u] = max(h1 + 1, h2);
    }
    else {
        p[u] = v;
        h[v] = max(h1 + 1, h2);
    }
};

int main() {
    p.assign(6, -1);
    h.assign(6, 0);

    unite(0,2);
    unite(3,4);
    unite(4,5);
    unite(3,5);

    for (int i = 0; i < 6; i++) {
        cout << "index: " << i << " | prerdst: " << get(i) << endl;
    }

    return 0;
}

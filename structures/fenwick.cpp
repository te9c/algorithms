#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// Fenwick tree in 1-indexation
template<typename T>
struct Fenwick {
    int n;
    vector<T> t;

    Fenwick(int _n) : n(_n + 1) {
        assert(_n >= 0);
        t.assign(n, 0);
    }
    Fenwick(const vector<T>& arr) {
        n = arr.size() + 1;
        t.resize(n);
        for (size_t i = 0; i < arr.size(); ++i) {
            add(i + 1, arr[i]);
        }
    }
    int F(int x) {
        return x - (x & (-x));
    }
    int F_rev(int x) {
        return x + (x & (-x));
    }
    T sum(int r) {
        assert(r >= 0 && r < n);
        T res = 0;
        for (; r > 0; r = F(r)) {
            res += t[r];
        }
        return res;
    }
    T sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }
    void add(int k, T x) {
        assert(1 <= k && k < n);
        for (; k < n; k = F_rev(k)) {
            t[k] += x;
        }
    }
};

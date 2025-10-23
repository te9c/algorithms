#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// scary!
struct SegmentTree {
    size_t ln = 1;
    static const int infc = INT_MAX;
    vector<int> st;
    vector<int> lazy;

    SegmentTree(size_t n, int default_value = infc) {
        while (ln <= n) {
            ln <<= 1;
        }
        st.assign(ln * 2, default_value);
        lazy.assign(ln * 2, infc);
    }
    SegmentTree(vector<int> a) : SegmentTree(a.size()) {
        for (size_t i = 0; i < a.size(); ++i) {
            st[ln + i] = a[i];
        }
        for (size_t i = ln - 1; i > 0; --i) {
            st[i] = min(st[i * 2], st[i * 2 + 1]);
        }
    }
    void push(int node) {
        if (lazy[node] == infc) return;
        st[node] += lazy[node];
        if (node < (int)ln) {
            if (lazy[node * 2] == infc) lazy[node * 2] = lazy[node];
            else lazy[node * 2] += lazy[node];

            if (lazy[node * 2 + 1] == infc) lazy[node * 2 + 1] = lazy[node];
            else lazy[node * 2 + 1] += lazy[node];
        }
        lazy[node]  = infc;
    }
    void add(int l, int r, int value) { add_internal(1, 0, ln - 1, l, r, value); }
    int query(int l, int r) { return query_internal(1, 0, ln - 1, l, r); }

    void add_internal(int node, int tl, int tr, int l, int r, int value) {
        push(node);
        if (tl >= l && tr <= r) {
            lazy[node] = value;
            push(node);
            return;
        }
        if (tl > r || tr < l) return;
        int tm = (tl + tr) / 2;
        add_internal(node * 2, tl, tm, l, r, value);
        add_internal(node * 2 + 1, tm + 1, tr, l, r, value);
        st[node] = min(st[node * 2], st[node * 2 + 1]);
    }
    int query_internal(int node, int tl, int tr, int l, int r) {
        push(node);
        if (tl >= l && tr <= r)
            return st[node];
        if (tl > r || tr < l)
            return infc;
        int tm = (tl + tr) / 2;
        return min(query_internal(node * 2, tl, tm, l, r), query_internal(node * 2 + 1, tm + 1, tr, l, r));
    }
};

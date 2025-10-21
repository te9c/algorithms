#include <bits/stdc++.h>

using namespace std;
using ll = long long;

struct SegmentTree {
    size_t ln = 1;
    vector<int> st;

    void init(size_t n) {
        while (ln <= n)
            ln <<= 1;
        st.assign(ln * 2, 0);
    }
    SegmentTree(size_t n) {
        init(n);
    }
    SegmentTree(const vector<int>& a) {
        init(a.size());
        for (size_t i = 0; i < a.size(); ++i) {
            st[i + ln] = a[i];
        }
        for (size_t i = ln - 1; i > 0; --i) {
            st[i] = st[i * 2] + st[i * 2 + 1];
        }
    }
    void set(int idx, int value) {
        idx += ln;
        st[idx] = value;
        idx >>= 1;
        while (idx > 0) {
            st[idx] = st[idx * 2] + st[idx * 2 + 1];
            idx >>= 1;
        }
    }
    void add(int idx, int value) { set(idx, st[idx + ln] + value); }
}    int sum(int l, int r) {
        l += ln;
        r += ln;
        int leftRes = 0, rightRes = 0;
        while (l < r) {
            if (l % 2 == 1) {
                leftRes = leftRes + st[l];
                ++l;
            }
            l >>= 1;
            if (r % 2 == 0) {
                rightRes = st[r] + rightRes;
                --r;
            }
            r >>= 1;
        }
        if (l == r)
            leftRes = leftRes + st[l];
        return leftRes + rightRes;
    }
;

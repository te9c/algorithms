#include <bits/stdc++.h>

using namespace std;
using ll = long long;

struct SegmentTree {
    size_t ln = 1;
    vector<int> st;

    void init(size_t n) {
        while (ln <= n)
            ln <<= 1;
        st.assign(ln * 2, INT_MIN);
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
            st[i] = max(st[i * 2], st[i * 2 + 1]);
        }
    }
    void set(int idx, int value) {
        idx += ln;
        st[idx] = value;
        idx >>= 1;
        while (idx > 0) {
            st[idx] = max(st[idx * 2], st[idx * 2 + 1]);
            idx >>= 1;
        }
    }
    void add(int idx, int value) { set(idx, st[idx + ln] + value); }
    int maxq(int l, int r) {
        l += ln;
        r += ln;
        int leftRes = INT_MIN, rightRes = INT_MIN;
        while (l < r) {
            if (l % 2 == 1) {
                leftRes = max(leftRes, st[l]);
                ++l;
            }
            l >>= 1;
            if (r % 2 == 0) {
                rightRes = max(st[r], rightRes);
                --r;
            }
            r >>= 1;
        }
        if (l == r)
            leftRes = max(leftRes, st[l]);
        return max(leftRes, rightRes);
    }
};



// TESTS

int stupid_max(vector<int>& a, int l, int r) {
    int ans = INT_MIN;
    for (int i = l; i <= r; ++i) {
        ans = max(ans, a[i]);
    }
    return ans;
}

int main() {
#define N 10000
#define Q 10000
#define MAX_VALUE 10000
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

    vector<int> a(N);
    for (int i = 0; i < N; ++i) {
        a[i] = rng() % MAX_VALUE;
    }
    SegmentTree st(a);

    for (int i = 0; i < Q; ++i) {
        int type = rng() % 2;
        if (type == 0) {
            int l = rng() % N;
            int r = l + rng() % (N - l);

            int val1 = st.maxq(l,r);
            int val2 = stupid_max(a, l, r);
            assert(val1 == val2);
        } else {
            int new_val = rng() % MAX_VALUE;
            int idx = rng() % N;
            st.set(idx, new_val);
            a[idx] = new_val;
        }
    }

    return 0;
}

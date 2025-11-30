#include <bits/stdc++.h>

using namespace std;
using ll = long long;

struct SuffArray {
#define ALPHABET_SIZE 256
    string s;
    int n;
    vector<int> suff_array;

    SuffArray(const string& _s) : s(_s + "#"), n(s.size()) {
        suff_array.assign(s.size(), 0);
        build();
    }
    void build() {
        vector<int> p(n);
        vector<int> c(n);
        vector<int> cnt(ALPHABET_SIZE, 0);
        int classes = 1;
        int k = 1;
        while ((1 << k) < n) {
            ++k;
        }

        for (int i = 0; i < n; ++i) {
            ++cnt[s[i]];
        }
        for (int i = 1; i < ALPHABET_SIZE; ++i) {
            cnt[i] += cnt[i - 1];
        }
        for (int i = 0; i < n; ++i) {
            p[--cnt[s[i]]] = i;
        }
        for (int i = 1; i < n; ++i) {
            if (s[p[i]] != s[p[i-1]])
                ++classes;
            c[p[i]] = classes - 1;
        }

        for (int h = 0; h < k; ++h) {
            vector<int> pn(n), cn(n);
            for (int i = 0; i < n; ++i) {
                pn[i] = p[i] - (1 << h);
                if (pn[i] < 0)
                    pn[i] += n;
            }
            cnt.assign(classes, 0);
            for (int i = 0; i < n; ++i) {
                ++cnt[c[pn[i]]];
            }
            for (int i = 1; i < classes; ++i) {
                cnt[i] += cnt[i - 1];
            }
            for (int i = n - 1; i >= 0; --i) {
                p[--cnt[c[pn[i]]]] = pn[i];
            }
            classes = 1;
            for (int i = 1; i < n; ++i) {
                int mid1 = (p[i] + (1<<h)) % n,  mid2 = (p[i-1] + (1<<h)) % n;
		if (c[p[i]] != c[p[i-1]] || c[mid1] != c[mid2])
			++classes;
		cn[p[i]] = classes-1;
            }
            c = cn;
        }
        suff_array = p;
    }
};

vector<int> get_lcp_array(const string& s, const vector<int>& sa) {
    int n = sa.size();
    vector<int> lcp(n - 1), pos(n);
    for (int i = 0; i < n; ++i) {
        pos[sa[i]] = i;
    }
    int k = 0;
    for (int i = 0; i < n; ++i) {
        if (k > 0)
            --k;
        if (pos[i] == n - 1) {
            k = 0;
            continue;
        }
        int j = sa[pos[i] + 1];
        while (max(i + k, j + k) < n && s[i + k] == s[j + k]) {
            ++k;
        }
        lcp[pos[i]] = k;
    }
    return lcp;
}

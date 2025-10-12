#include <bits/stdc++.h>

using namespace std;

// Z-function algorithm
vector<int> z_func(const string& s) {
    vector<int> z(s.size(), 0);
    int l = 0;
    int r = 0;
    for (int i = 1; i < (int)s.size(); ++i) {
        z[i] = max(0, min(r - i, z[i - l]));

        while (i + z[i] < (int)s.size() && s[i + z[i]] == s[z[i]])
            ++z[i];

        if (i + z[i] > r) {
            r = i + z[i];
            l = i;
        }
    }
    z[0] = s.size();
    return z;
}

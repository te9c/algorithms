#include <bits/stdc++.h>

using ll = long long;
using ld = long double;
using ull = unsigned long long int;

#define pi pair<int, int>
#define pl pair<ll, ll>
#define pd pair<ld, ld>

#define vi vector<int>
#define vl vector<ll>
#define vd vector<ld>
#define vpi vector<pi>
#define vpl vector<pl>
#define vpd vector<pd>

#define forf(i, m, n) for(int i = m; i <= (int)n; i++)
#define forb(i, m, n) for(int i = m; i >= (int)n; i--)

#define pb push_back
#define f first
#define s second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
#define lb lower_bound
#define up upper_bound

using namespace std;

inline int gcd(int a, int b) {
    for (; b > 0; a %= b, swap(a, b)) {}
    return a;
}

// end of template

vector<int> A,ST;

void build(int node, int L, int R) {
    if (L == R) {
        ST[node] = A[L];
    }
    else {
        // Find the middle element to
        // split the array into two halves
        int mid = (L + R) / 2;

        // Recursively travel the
        // left half
        build(2 * node, L, mid);

        // Recursively travel the
        // right half
        build(2 * node + 1, mid + 1, R);

        // Storing the sum of both the
        // children into the parent
        ST[node] = ST[2 * node] + ST[2 * node + 1];
    }
}

void update(int node, int L, int R, int idx, int val) {
    // Find the lead node and
    // update its value
    if (L == R) {
        A[idx] += val;
        ST[node] += val;
    }
    else {
        // Find the mid
        int mid = (L + R) / 2;

        // If node value idx is at the
        // left part then update
        // the left part
        if (L <= idx and idx <= mid)
            update(2 * node, L, mid, idx, val);
        else
            update(2 * node + 1, mid + 1, R, idx, val);

        // Store the information in parents
        ST[node] = ST[2 * node] + ST[2 * node + 1];
    }
}

int query(int node, int tl, int tr, int l, int r) {

    // If it lies out of range then
    // return 0
    if (r < tl or tr < l) {
        return 0;
    }

    // If the node conains the range then
    // return the node value
    if (l <= tl and tr <= r)
        return ST[node];
    int tm = (tl+tr)/2;

    return query(2 * node, tl, tm, l, r)
        + query(2*node + 1, tm + 1, tr, l, r);
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n = 6;
    A = { 0, 1, 3, 5, -2, 3};

    ST.resize(4 * n);
    build(1,0,n-1);

    cout << "Sum of values in range 0-4 are:"
        << query(1,0,n-1,0,4) << endl;

    update(1,0,n-1,1,100);
    cout << "Value at index 1 increase by 100\n";
    cout << "sum of value in range 1-3 are: "
        << query (1, 0, n-1, 1 , 3) << '\n';

    return 0;
}

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

ll binpow (ll a, ll n, ll modulo) {
	ll res = 1;
	while (n) {
		if (n & 1)
			res = (res * a) % modulo;
		a = (a * a) % modulo;
		n >>= 1;
	}
	return res;
}

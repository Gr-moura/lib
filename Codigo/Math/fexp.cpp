#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// Exponenciacao rapida
//
// (x^y mod m) em O(log(y))

ll fexp(ll x, ll y, ll m)
{ // iterativo
    ll ret = 1;
    while (y)
    {
        if (y & 1) ret = (ret * x) % m;
        y >>= 1;
        x = (x * x) % m;
    }
    return ret;
}

ll fexp(ll x, ll y, ll m)
{ // recursivo
    if (!y) return 1;
    ll ans = fexp(x * x % m, y / 2, m);
    return y % 2 ? x * ans % m : ans;
}
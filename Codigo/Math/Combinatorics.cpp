#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// Exponenciacao rapida
// (x^y mod m) em O(log(y))

ll fexp(ll x, ll y, ll m)
{
    ll ret = 1;
    while (y)
    {
        if (y & 1) ret = (ret * x) % m;
        y >>= 1;
        x = (x * x) % m;
    }
    return ret;
}

// Inverso modular de x mod m, onde m é primo
// O (log m)
ll inv(ll x, ll m)
{
    // Usando o pequeno teorema de Fermat

    // x^(m-1) ≡ 1 (mod m)
    // x*x^(m-2) ≡ 1 (mod m)

    // Portanto, o inverso modular de x é x^(m-2) mod m

    return fexp(x, m - 2, m);
}

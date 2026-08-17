#include <bits/stdc++.h>
using namespace std;

/* clang-format on */
// SegTree Beats
//
// Suporta as operações:
// query(a, b) - sum(v[a..b])
// updateMod(a, b, x) faz com que v[i] <- v[i] % x,
// para i em [a, b]
// updateSet(i, x) faz com que v[i] <- x
//
// Complexidade: O( (n + q) * log n * log C ),
// onde n é o tam de v, q é o número de queries (qualquer uma das três suportadas), e C é o maior valor possível em v

using ll = long long;
const int MAX = 100000;

namespace beats
{
struct node
{
    int tam;
    ll sum, maxVal;

    node(ll x = 0)
    {
        sum = x;
        maxVal = x;
    }

    node(const node &l, const node &r)
    {
        sum = l.sum + r.sum;
        maxVal = max(l.maxVal, r.maxVal);
    }
};

node seg[4 * MAX];
int n, *v;

node build(int p = 1, int l = 0, int r = n - 1)
{
    if (l == r) return seg[p] = {v[l]};
    int m = (l + r) / 2;
    return seg[p] = {build(2 * p, l, m), build(2 * p + 1, m + 1, r)};
}

void build(int n2, int *v2)
{
    n = n2, v = v2;
    build();
}

void updateMod(int a, int b, ll x, int p = 1, int l = 0, int r = n - 1)
{
    // Não precisamos fazer mod, já que, ou está fora do range, ou já está em [0, x - 1]
    if (b < l or r < a or seg[p].maxVal < x) return;

    if (l == r)
    {
        seg[p].maxVal %= x;
        seg[p].sum %= x;
        return;
    }

    int m = (l + r) / 2;

    updateMod(a, b, x, 2 * p, l, m);
    updateMod(a, b, x, 2 * p + 1, m + 1, r);

    seg[p] = node(seg[2 * p], seg[2 * p + 1]);
}

void updateSet(int i, ll x, int p = 1, int l = 0, int r = n - 1)
{
    if (l == r)
    {
        seg[p].sum = x;
        seg[p].maxVal = x;
        return;
    }

    int m = (l + r) / 2;

    if (i <= m) updateSet(i, x, 2 * p, l, m);
    else updateSet(i, x, 2 * p + 1, m + 1, r);

    seg[p] = node(seg[2 * p], seg[2 * p + 1]);
}

// Retorna a soma no intervalo [a, b]
ll query(int a, int b, int p = 1, int l = 0, int r = n - 1)
{
    if (b < l || r < a) return 0;
    if (a <= l && r <= b) return seg[p].sum;

    int m = (l + r) / 2;
    return query(a, b, 2 * p, l, m) + query(a, b, 2 * p + 1, m + 1, r);
}

}; // namespace beats

#include <bits/stdc++.h>
using namespace std;

// SegTree de soma
// Query e Update em O(log(n))
// Build em O(n)

const int MAX = 1e5 + 10;

int a[MAX];
int seg[4 * MAX];

// p: posição do nó atual na segtree
// l, r: intervalo representado por este nó no vetor original

// build(1, 0, n - 1); -> Começamos na raiz, que representa o intervalo [0, n - 1]
int build(int p, int l, int r)
{
    // Caso base: folha, achamos o valor diretamente do vetor original
    if (l == r) return seg[p] = a[l];

    // Dividimos o intervalo em dois e construímos os filhos
    int mid = l + (r - l) / 2;
    return seg[p] = build(2 * p, l, mid) + build(2 * p + 1, mid + 1, r);
}

// Query na range [a, b] do vetor original (0-indexed)
// query(a, b, 1, 0, n - 1); -> Começamos na raiz, que representa o intervalo [0, n - 1]
int query(int a, int b, int p, int l, int r)
{
    // Caso base: intervalo totalmente fora da query
    if (b < l or a > r) return 0;

    // Caso base: intervalo totalmente dentro da query
    if (l >= a and r <= b) return seg[p];

    // Dividimos o intervalo em dois e consultamos os filhos
    int mid = l + (r - l) / 2;
    return query(a, b, 2 * p, l, mid) + query(a, b, 2 * p + 1, mid + 1, r);
}

// Update na posição i do vetor original para o valor v
// update(i, v, 1, 0, n - 1); -> Começamos na raiz, que representa o intervalo [0, n - 1]
int update(int i, int v, int p, int l, int r)
{
    if (l == r and l == i) return seg[p] = v;
    if (i < l or i > r) return seg[p];

    int mid = l + (r - l) / 2;
    return seg[p] = update(i, v, 2 * p, l, mid) + update(i, v, 2 * p + 1, mid + 1, r);
}

void solve()
{
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; i++)
        cin >> a[i];

    build(1, 0, n - 1);

    for (int i = 0; i < m; i++)
    {
        int tipo;
        cin >> tipo;
        if (tipo == 1)
        {
            int i, v;
            cin >> i >> v;

            update(i, v, 1, 0, n - 1);
            continue;
        }

        int l, r;
        cin >> l >> r;
        cout << query(l, r - 1, 1, 0, n - 1) << endl;
    }
}

#include <bits/stdc++.h>
using namespace std;

// SegTree de Assigment
// Query e Update em O(log(n))
// Build em O(n)

const int MAX = 1e5 + 10;
int n;
int a[MAX];
int seg[4 * MAX], toUpdate[4 * MAX];

void propagate(int p) 
{
    if (toUpdate[p]) 
	{
        seg[p * 2] = seg[p * 2 + 1] = seg[p];
 
		toUpdate[p * 2] = toUpdate[p * 2 + 1] = true;
        toUpdate[p] = false;
    }
}

// p: posição do nó atual na segtree
// tl, tr: intervalo, no vetor original, representado por este nó da árvore

// build(); -> Começamos na raiz, que representa o intervalo [0, n - 1]
int build(int p = 1, int tl = 0, int tr = n - 1)
{
    // Caso base: folha, achamos o valor diretamente do vetor original
    if (tl == tr) return seg[p] = a[tl];

    // Dividimos o intervalo em dois e construímos os filhos
    int tm = tl + (tr - tl) / 2;
    return seg[p] = build(2 * p, tl, tm) + build(2 * p + 1, tm + 1, tr);
}

// Query na range [l, r] do vetor original (0-indexed)
// query(l, r); -> Começamos na raiz, que representa o intervalo [0, n - 1]
int query(int l, int r, int p = 1, int tl = 0, int tr = n - 1)
{
    // Caso base: intervalo totalmente fora da query
    if (r < tl or l > tr) return 0;

    // Caso base: intervalo totalmente dentro da query
    if (tl >= l and tr <= r) return seg[p];

    // Dividimos o intervalo em dois e consultamos os filhos
    int tm = tl + (tr - tl) / 2;
    return query(l, r, 2 * p, tl, tm) + query(l, r, 2 * p + 1, tm + 1, tr);
}

// Update na posição ind do vetor original para o valor v
// update(ind, v); -> Começamos na raiz, que representa o intervalo [0, n - 1]
void update(int l, int r, int v, int p = 1, int tl = 0, int tr = n - 1)
{
	propagate(p);

    // Caso base: intervalo totalmente fora da query
    if (r < tl or l > tr) return;

    // Caso base: intervalo totalmente dentro da query
    if (tl >= l and tr <= r) 
	{	
		seg[p] = v;
		return;
	}

    int tm = tl + (tr - tl) / 2;
    update(l, r, v, 2 * p, tl, tm);
	update(l, r, v, 2 * p + 1, tm + 1, tr);
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

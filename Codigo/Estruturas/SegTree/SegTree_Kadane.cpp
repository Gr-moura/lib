#include <bits/stdc++.h>
#define int long long
using namespace std;

// SegTree de Kadane
// Retorna o máximo subarray sum em O(log(n)) por query,
// considerando que o subarray vazio é permitido.

// Query e Update em O(log(n))
// Build em O(n)

const int MAXN = 1e5 + 10;

struct node {
	int sum = 0;
	int maxPref = 0;
	int maxSuf = 0;
	int max = 0;
};

node seg[4 * MAXN];
int v[MAXN];

// O max subarray sum ou está contido completamente nos filhos ou é a soma 
// do maior sufixo do filho da esquerda com o maior prefixo do filho da direita
node merge(node n1, node n2)
{
	node resp;
	
	resp.sum = n1.sum + n2.sum;
	resp.maxPref = max(n1.maxPref, n1.sum + n2.maxPref);
	resp.maxSuf = max(n2.maxSuf, n2.sum + n1.maxSuf);
	resp.max = max({n1.max, n2.max, n1.maxSuf + n2.maxPref});

	return resp;
}


// pos: posição do nó atual na segtree
// ini, fim: intervalo, no vetor original, representado por este nó da árvore

// build(); -> Começamos na raiz, que representa o intervalo [0, n - 1]
void build(int pos, int ini, int fim)
{
    // Caso base: folha, achamos o valor diretamente do vetor original
    if (ini == fim) 
	{
		seg[pos].sum = v[ini];
		seg[pos].maxPref = max(0ll, v[ini]);
		seg[pos].maxSuf = max(0ll, v[ini]);
		seg[pos].max = max(0ll, v[ini]);

		return;
	}

    // Dividimos o intervalo em dois e construímos os filhos
    int mid = ini + (fim - ini) / 2;
	int esq = 2 * pos, dir = 2 * pos + 1;

    build(esq, ini, mid);
    build(dir, mid + 1, fim);

    seg[pos] = merge(seg[esq], seg[dir]);
}

// Query na range [p, q] do vetor original (0-indexed)
// query(p, q); -> Começamos na raiz, que representa o intervalo [0, n - 1]
node query(int pos, int ini, int fim, int p, int q)
{
    // Caso base: intervalo totalmente fora da query
    if (q < ini || p > fim) return {0, 0, 0, 0};

    // Caso base: intervalo totalmente dentro da query
    if (p <= ini && fim <= q) return seg[pos];

    // Dividimos o intervalo em dois e consultamos os filhos
    int mid = ini + (fim - ini) / 2;
	int esq = 2 * pos, dir = 2 * pos + 1;

    return merge(query(esq, ini, mid, p, q), query(dir, mid + 1, fim, p, q));
}

// Update na posição id do vetor original para o valor val
// update(id, val); -> Começamos na raiz, que representa o intervalo [0, n - 1]
void update(int pos, int ini, int fim, int id, int val)
{
    if (id < ini || id > fim) return;
	if (ini == fim) 
	{
		seg[pos].sum = val;
		seg[pos].maxPref = max(0ll, val);
		seg[pos].maxSuf = max(0ll, val);
		seg[pos].max = max(0ll, val);

		return;
	}

    int mid = ini + (fim - ini) / 2;
	int esq = 2 * pos, dir = 2 * pos + 1;

	update(esq, ini, mid, id, val);
	update(dir, mid + 1, fim, id, val);

    seg[pos] = merge(seg[esq], seg[dir]);
}

void solve()
{
    int n, m;
    cin >> n >> m;

	memset(v, 0, sizeof(v));
    for (int i = 0; i < n; i++)
        cin >> v[i];

    build(1, 0, n - 1);
    cout << query(1, 0, n - 1, 0, n - 1).max << endl;
    for (int i = 0; i < m; i++)
    {
		int id, val;
		cin >> id >> val;

		update(1, 0, n - 1, id, val);
        cout << query(1, 0, n - 1, 0, n - 1).max << endl;
    }
}

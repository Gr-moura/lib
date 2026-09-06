#include <bits/stdc++.h>
using namespace std;

// SegTree de soma
// Query e Update em O(log(n))
// Build em O(n)

const int MAXN = 1e5 + 10;

int seg[4 * MAXN];
int v[MAXN];

// pos: posição do nó atual na segtree
// ini, fim: intervalo, no vetor original, representado por este nó da árvore

// build(); -> Começamos na raiz, que representa o intervalo [0, n - 1]
void build(int pos, int ini, int fim)
{
    // Caso base: folha, achamos o valor diretamente do vetor original
    if (ini == fim) 
	{
		seg[pos] = v[ini];
		return;
	}

    // Dividimos o intervalo em dois e construímos os filhos
    int mid = ini + (fim - ini) / 2;
	int esq = 2 * pos, dir = 2 * pos + 1;

    build(esq, ini, mid);
    build(dir, mid + 1, fim);

    seg[pos] = seg[esq] + seg[dir];
}

// Query na range [p, q] do vetor original (0-indexed)
// query(p, q); -> Começamos na raiz, que representa o intervalo [0, n - 1]
int query(int pos, int ini, int fim, int p, int q)
{
    // Caso base: intervalo totalmente fora da query
    if (q < ini || p > fim) return 0;

    // Caso base: intervalo totalmente dentro da query
    if (p <= ini && fim <= q) return seg[pos];

    // Dividimos o intervalo em dois e consultamos os filhos
    int mid = ini + (fim - ini) / 2;
	int esq = 2 * pos, dir = 2 * pos + 1;

    return query(esq, ini, mid, p, q) + query(dir, mid + 1, fim, p, q);
}

// Retorna o menor índice i cuja soma de prefixo v[0] + ... + v[i] é >= target
// Os valores do vetor devem ser não negativos, inclusive após updates
// Retorna -1 se a soma total for menor que target
// firstPrefixAtLeast(target); -> Começamos na raiz, que representa o intervalo [0, n - 1]
int firstPrefixAtLeast(int pos, int ini, int fim, int target)
{
	// O target não está no nó atual
	if (target > seg[pos]) return -1;

	// Ele está no nó atual e esse nó é uma folha
	if (ini == fim) return ini;

	int mid = ini + (fim - ini) / 2;
	int esq = 2 * pos, dir = 2 * pos + 1;

	// Se a soma da esquerda é suficiente, a resposta está nela
	if (seg[esq] >= target) return firstPrefixAtLeast(esq, ini, mid, target);

	// Caso contrário, desconta a soma da esquerda e procura à direita
	return firstPrefixAtLeast(dir, mid + 1, fim, target - seg[esq]);
}

// Retorna o índice do k-ésimo 1 em um vetor binário, com k indexado em 1
// Pré-condições: o vetor é binário e k >= 1
// Retorna -1 se o vetor tiver menos de k elementos iguais a 1
// findKth(k); -> Começamos na raiz, que representa o intervalo [0, n - 1]
int findKth(int pos, int ini, int fim, int k)
{
	// Em um vetor binário, a soma de prefixo conta quantos elementos 1 apareceram
	// Logo, o k-ésimo 1 está no primeiro prefixo cuja soma é >= k
	return firstPrefixAtLeast(pos, ini, fim, k);
}

// Update na posição id do vetor original para o valor val
// update(id, val); -> Começamos na raiz, que representa o intervalo [0, n - 1]
void update(int pos, int ini, int fim, int id, int val)
{
    if (id < ini || id > fim) return;
	if (ini == fim) 
	{
		seg[pos] = val;
		return;
	}

    int mid = ini + (fim - ini) / 2;
	int esq = 2 * pos, dir = 2 * pos + 1;

	update(esq, ini, mid, id, val);
	update(dir, mid + 1, fim, id, val);

    seg[pos] = seg[esq] + seg[dir];
}

void solve()
{
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; i++)
        cin >> v[i];

    build(1, 0, n - 1);

    for (int i = 0; i < m; i++)
    {
        int tipo;
        cin >> tipo;
        if (tipo == 1)
        {
            int i, val;
            cin >> i >> val;

            update(1, 0, n - 1, i, val);
            continue;
        }

        int p, q;
        cin >> p >> q;
        cout << query(1, 0, n - 1, p, q) << endl;
    }
}

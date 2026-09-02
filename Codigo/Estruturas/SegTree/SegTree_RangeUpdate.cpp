#include <bits/stdc++.h>
using namespace std;

// SegTree para Range Update e Point Query
//
// Soma val a todas as posições do intervalo [p, q] e consulta o valor
// acumulado em uma única posição id
//
// Quando os updates são em intervalos, mas as queries são pontuais, não
// precisamos de lazy propagation. Decompomos [p, q] em nós totalmente cobertos
// e guardamos val nesses nós, sem propagá-lo para os filhos. Na query de id,
// somamos os valores guardados no caminho da raiz até a folha de id. Cada update
// que contém id contribui em exatamente um nó desse caminho
//
// Update e query em O(log(n)); memória em O(n)
// Os intervalos são inclusivos e 0-indexed
// Inicialmente, todos os elementos valem 0

const int MAXN = 1e5 + 10;

// seg[pos] guarda o incremento aplicado a todo o intervalo [ini, fim]
int seg[4 * MAXN];

// Soma val a todas as posições do intervalo [p, q]
// update(p, q, val) -> Começamos na raiz, que representa [0, n - 1]
void update(int pos, int ini, int fim, int p, int q, int val)
{
    // Caso base: intervalo totalmente fora do update
    if (q < ini || p > fim) return;

    // Caso base: intervalo totalmente dentro do update
    if (p <= ini && fim <= q) 
	{
		// Guardamos o incremento neste nó sem propagá-lo para os filhos
		seg[pos] += val;
		return;
	}

    // Dividimos o intervalo em dois e atualizamos os filhos
    int mid = ini + (fim - ini) / 2;
	int esq = 2 * pos, dir = 2 * pos + 1;

	update(esq, ini, mid, p, q, val);
	update(dir, mid + 1, fim, p, q, val);
}

// Consulta o valor acumulado na posição id
// query(id) -> Começamos na raiz e somamos os incrementos até a folha de id
int query(int pos, int ini, int fim, int id)
{
    // Intervalo fora do caminho até id
    if (id < ini or id > fim) return 0;

	// Na folha, retornamos o incremento guardado nela
	if (ini == fim) return seg[pos];

    int mid = ini + (fim - ini) / 2;
	int esq = 2 * pos, dir = 2 * pos + 1;

	// seg[pos] afeta id; apenas um dos filhos terá uma contribuição não nula
	return seg[pos] + query(esq, ini, mid, id) + query(dir, mid + 1, fim, id);
}

void solve()
{
    int n, m;
    cin >> n >> m;

	memset(seg, 0, sizeof(seg));

    for (int i = 0; i < m; i++)
    {
        int tipo;
        cin >> tipo;
        if (tipo == 1)
        {
            int l, r, v;
            cin >> l >> r >> v;

            // A entrada usa [l, r); update recebe um intervalo inclusivo
            update(1, 0, n - 1, l, r - 1, v);
            continue;
        }

        int id;
        cin >> id;
        cout << query(1, 0, n - 1, id) << endl;
    }
}

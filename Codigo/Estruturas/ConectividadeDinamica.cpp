#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;
const int MAX = 1e5 + 10;

// Conectividade Dinâmica - Q queries (adição e remoção de arestas)
// Custo por operação: Q * log(Q) ^ 2

// Cada aresta aparece em O(log(Q)) nós da Segment Tree, e cada união
// custa O(log(Q)) amortizado. Logo, o custo total é O(Q * log(Q) ^ 2).
// Custo de memória: O(Q * log(Q))

// Guarda as arestas existentes na forma de uma Segment Tree
vector<pii> tree[MAX * 4];

// Adiciona no intervalo [a, b] a aresta e.
// add (a, b, e, 1, 0, q - 1); -> Começamos na raiz, que representa o intervalo [0, q - 1]
void add(int a, int b, pii e, int p, int l, int r)
{
    // Caso base: intervalo totalmente fora da query
    if (b < l or a > r) return;

    // Caso base: intervalo totalmente dentro da query
    if (l >= a and r <= b)
    {
        tree[p].push_back(e);
        return;
    }

    int mid = l + (r - l) / 2;

    add(a, b, e, p * 2, l, mid);
    add(a, b, e, p * 2 + 1, mid + 1, r);
}

// Representa uma aresta temporária em um grafo
struct arestaTemporaria
{
    // Vértices da aresta
    int u, v;

    // Intervalo de tempo em que a aresta existe [l, r]
    int l, r;

    arestaTemporaria(int u, int v, int l, int r) : u(u), v(v), l(l), r(r) {}

    void print() { cout << "u: " << u + 1 << " v: " << v + 1 << " l: " << l << " r: " << r << endl; }
};

// Endereco que foi modificado e antigo valor
vector<pair<int *, int>> operacoes;

// Resetamos até termos uma quantidade x de operações já realizadas
void cancelaOperacao(int qt)
{
    while (operacoes.size() > qt)
    {
        auto ultimo = operacoes.back();
        operacoes.pop_back();

        *ultimo.first = ultimo.second;
    }
}

// DSU
struct DSU
{
    int qtComponentes;
    vector<int> id, sz;

    DSU(int N) : id(N), sz(N, 1)
    {
        qtComponentes = N;
        iota(id.begin(), id.end(), 0);
    }

    // Encontra o representante do conjunto de x em O(log(n))
    int find(int x)
    {
        while (x != id[x])
            x = id[x];
        return x;
    }

    // Une em O(log(n)), salvando as operações realizadas
    void unite(int x, int y)
    {
        x = find(x), y = find(y);
        if (x == y) return;

        if (sz[x] < sz[y]) swap(x, y);

        // Valor antes de unir
        operacoes.emplace_back(&id[y], id[y]);
        id[y] = x;

        if (sz[x] == sz[y])
        {
            operacoes.emplace_back(&sz[x], sz[x]);
            sz[x] += 1;
        }

        operacoes.emplace_back(&qtComponentes, qtComponentes);
        qtComponentes--;
    }
};

void dfs(DSU &dsu, int id, int l, int r)
{
    int total = operacoes.size();

    // Aplica as arestas do nó atual (id) da segtree
    for (auto p : tree[id])
    {
        dsu.unite(p.first, p.second);
    }
    // Chegamos em uma folha, ou seja, uma query em específico
    if (l == r)
    {
        // Resposta da query

        // Reseta o estado para antes de processar este nó
        cancelaOperacao(total);
        return;
    }

    // Continua para os filhos
    int mid = (l + r) / 2;

    dfs(dsu, id * 2, l, mid);         // Left child
    dfs(dsu, id * 2 + 1, mid + 1, r); // Right child

    // Reseta o estado para antes de processar este nó
    cancelaOperacao(total);
}

void solve()
{
    int n, m, k;
    cin >> n >> m >> k;

    // Recebe uma aresta e retorna a última vez em que esteve viva;
    map<pii, int> arestas;

    vector<arestaTemporaria> ranges;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        u--, v--;

        // Todas essas existiam desde o primeiro momento
        if (u > v) swap(u, v);
        arestas[{u, v}] = 0;
    }

    for (int i = 1; i <= k; i++)
    {
        int t, u, v;
        cin >> t >> u >> v;
        u--, v--;

        if (u > v) swap(u, v);

        if (t == 1)
        {
            arestas[{u, v}] = i;
            continue;
        }

        arestaTemporaria temp(u, v, arestas[{u, v}], i - 1);
        arestas.erase({u, v});
        ranges.push_back(temp);
    }

    for (auto [p, l] : arestas)
    {
        arestaTemporaria temp(p.first, p.second, l, k);
        ranges.push_back(temp);
    }

    for (auto p : ranges)
    {
        add(p.l, p.r, {p.u, p.v}, 1, 0, k);
    }

    DSU dsu(n);
    dfs(dsu, 1, 0, k);
}
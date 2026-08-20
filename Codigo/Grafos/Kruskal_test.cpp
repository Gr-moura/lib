#include <bits/stdc++.h>
using namespace std;

// Teste para o algoritmo de Kruskal (Codigo/Grafos/Kruskal.cpp).
//
// Como Kruskal.cpp é um trecho de biblioteca (usa DSU antes da sua definição
// e assume um vetor global `edg`), este arquivo replica a implementação numa
// ordem compilável e a exercita com um grafo conhecido para verificar se a
// AGM retornada tem o peso total e as arestas esperadas.

using ll = long long;

struct DSU
{
    vector<int> id, sz;

    DSU(int n) : id(n), sz(n, 1) { iota(id.begin(), id.end(), 0); }
    int find(int a) { return a == id[a] ? a : id[a] = find(id[a]); }

    void unite(int a, int b)
    {
        a = find(a), b = find(b);
        if (a == b) return;
        if (sz[a] < sz[b]) swap(a, b);
        sz[a] += sz[b], id[b] = a;
    }
};

vector<tuple<int, int, int>> edg; // {peso, x, y}

pair<ll, vector<tuple<int, int, int>>> kruskal(int n)
{
    DSU dsu(n);
    sort(edg.begin(), edg.end());

    ll cost = 0;
    vector<tuple<int, int, int>> mst;

    for (auto [w, x, y] : edg)
        if (dsu.find(x) != dsu.find(y))
        {
            mst.emplace_back(w, x, y);
            cost += w;

            dsu.unite(x, y);
        }

    return {cost, mst};
}

// Normaliza uma aresta (peso, u, v) garantindo u <= v para comparação
// independente da ordem em que os vértices foram inseridos.
static tuple<int, int, int> norm(tuple<int, int, int> e)
{
    auto [w, u, v] = e;
    if (u > v) swap(u, v);
    return {w, u, v};
}

static void expect(bool cond, const string &msg)
{
    if (!cond)
    {
        cerr << "FALHOU: " << msg << endl;
        exit(1);
    }
    cout << "OK: " << msg << endl;
}

int main()
{
    // Grafo de teste (n = 5 vértices, 7 arestas):
    //
    //   Arestas (u, v, peso):
    //     (0, 1, 1)
    //     (0, 2, 3)
    //     (1, 2, 2)
    //     (1, 3, 4)
    //     (2, 3, 5)
    //     (3, 4, 6)
    //     (2, 4, 7)
    //
    // AGM esperada (peso total = 13):
    //   (0, 1, 1), (1, 2, 2), (1, 3, 4), (3, 4, 6)
    int n = 5;
    edg = {
        {1, 0, 1},
        {3, 0, 2},
        {2, 1, 2},
        {4, 1, 3},
        {5, 2, 3},
        {6, 3, 4},
        {7, 2, 4},
    };

    auto [cost, mst] = kruskal(n);

    expect(cost == 13, "peso total da AGM == 13 (obtido " + to_string(cost) + ")");
    expect((int)mst.size() == n - 1,
           "AGM contém n-1 = 4 arestas (obtido " + to_string(mst.size()) + ")");

    set<tuple<int, int, int>> got;
    for (auto e : mst) got.insert(norm(e));

    set<tuple<int, int, int>> expected = {
        {1, 0, 1},
        {2, 1, 2},
        {4, 1, 3},
        {6, 3, 4},
    };
    expect(got == expected, "conjunto de arestas da AGM corresponde ao esperado");

    // Verifica que a AGM conecta todos os vértices (é de fato uma árvore geradora).
    DSU check(n);
    for (auto [w, u, v] : mst) check.unite(u, v);
    int root = check.find(0);
    bool connected = true;
    for (int v = 1; v < n; v++) connected = connected && (check.find(v) == root);
    expect(connected, "AGM conecta todos os vértices");

    cout << "\nTodos os testes de Kruskal passaram." << endl;
    return 0;
}

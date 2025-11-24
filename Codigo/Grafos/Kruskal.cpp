#include <bits/stdc++.h>
using namespace std;

// Kruskal
//
// Gera e retorna uma AGM e seu custo total a partir do vetor de arestas (edg)
// do grafo
//
// O(m log(m) + m(a(n))), onde m é o número de arestas, n o número de vértices e a(n)
// é a função inversa de Ackermann

using ll = long long;

vector<tuple<int, int, int>> edg; // {peso,[x,y]}
pair<ll, vector<tuple<int, int, int>>> kruskal(int n)
{
    DSU dsu(n);
    sort(edg.begin(), edg.end());

    ll cost = 0;
    vector<tuple<int, int, int>> mst;

    // Tenta adicionar a aresta (x, y) de menor peso. Se não formar ciclo, adiciona à AGM
    for (auto [w, x, y] : edg)
        if (dsu.find(x) != dsu.find(y))
        {
            mst.emplace_back(w, x, y);
            cost += w;

            dsu.unite(x, y);
        }

    return {cost, mst};
}

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
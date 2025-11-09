#include <bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;

// DSU
//
// Une dois conjuntos e acha a qual conjunto um elemento pertence por seu id
// find e unite: O(a(n)) ~= O(1) amortizado

struct dsu
{
    vector<int> id, sz;

    dsu(int n) : id(n), sz(n, 1) { iota(id.begin(), id.end(), 0); }

    int find(int a) { return a == id[a] ? a : id[a] = find(id[a]); }

    void unite(int a, int b)
    {
        a = find(a), b = find(b);
        if (a == b) return;
        if (sz[a] < sz[b]) swap(a, b);
        sz[a] += sz[b], id[b] = a;
    }
};

// DSU de bipartido
//
// Une dois vertices e acha a qual componente um vertice pertence
// Informa se a componente de um vertice e bipartida
//
// find e unite: O(log(n))

struct dsu
{
    vector<int> id, sz, bip, c;

    dsu(int n) : id(n), sz(n, 1), bip(n, 1), c(n) { iota(id.begin(), id.end(), 0); }

    int find(int a) { return a == id[a] ? a : find(id[a]); }
    int color(int a) { return a == id[a] ? c[a] : c[a] ^ color(id[a]); }

    void unite(int a, int b)
    {
        bool change = color(a) == color(b);
        a = find(a), b = find(b);
        if (a == b)
        {
            if (change) bip[a] = 0;
            return;
        }

        if (sz[a] < sz[b]) swap(a, b);
        if (change) c[b] = 1;
        sz[a] += sz[b], id[b] = a, bip[a] &= bip[b];
    }
};

// DSU com extensões
// Union e find como antes, em
// Move (a, b): move um elemento a para o mesmo conjunto que b
// Erase (a): remove o elemento a do seu conjunto
// Fazemos isso criando um novo vértice "fantasma" (N + i) que representaria
// o conjunto do elemento i.

// Pequena otimização: o id do conjunto também guarda o seu tamanho (negativo)
struct DSU_Extensions
{
    vector<int> id;
    DSU_Extensions(int N) : id(2 * N, -1) { iota(id.begin(), id.begin() + N, N); }

    // O representante é aquele que guarda o tamanho negativo
    int find(int x) { return id[x] < 0 ? x : id[x] = find(id[x]); }

    bool unite(int x, int y)
    {
        if (isDel(x) || isDel(y)) return false;

        auto fx = find(x), fy = find(y);
        if (fx == fy) return false;

        if (id[fx] > id[fy]) swap(fx, fy);
        id[fx] += id[fy];

        id[fy] = fx;
        return true;
    }

    bool move(int x, int y)
    {
        if (isDel(x) || isDel(y)) return false;

        auto fx = find(x), fy = find(y);
        if (fx == fy) return false;

        // Remove o elemento do seu conjunto atual e adiciona ao novo
        id[fx]++, id[fy]--;
        id[x] = fy;
        return true;
    }

    bool erase(int x)
    {
        if (isDel(x)) return false;

        // Diminiui o tamanho do conjunto original
        auto fx = find(x);
        id[fx]++;

        // Elimina o elemento
        id[x] = -1;
        return true;
    }

    // Como nenhum elemento naturalmente terá -1, apenas os "fantasmas",
    // Podemos usar isso para checar se o elemento foi removido
    bool isDel(int x) { return id[x] == -1; }

    int sz(int x) { return -id[find(x)]; }
};
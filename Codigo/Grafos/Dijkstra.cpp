#include <bits/stdc++.h>
using namespace std;

// Dijkstra
//
// Calcula a menor distância do vértice inicial a todos os vértices alcançáveis
// em um grafo com pesos não negativos
//
// O((n + m) log(m)), onde n é o número de vértices e m o número de arestas
// alcançáveis a partir do vértice inicial
//
// g[v] contém pares {u, peso}, representando uma aresta de v para u
// Ao final, minDist[v] guarda a menor distância até v, ou LINF se v for inalcançável
// Para uma nova execução, minDist deve ser reinicializado com LINF

using pii = pair<int, int>;
const int MAX = 2e5 + 10;
const int LINF = 0x3f3f3f3f;

vector<int> minDist(MAX, LINF);
vector<vector<pii>> g(MAX);

void djikstra(int vInicial)
{
    // Min-heap de pares {custoAtual, vértice}
    priority_queue<pii, vector<pii>, greater<pii>> pq;
    pq.push({0, vInicial});

    while (!pq.empty())
    {
        // Extrai o vértice de menor custo
        auto [custoAtual, vAtual] = pq.top();
        pq.pop();

		// Se estamos em uma solução pior, ignoramos
        if (custoAtual >= minDist[vAtual]) continue;
        minDist[vAtual] = custoAtual;

        // Gera novas distâncias a partir dos vizinhos de vAtual
        for (auto [u, custoAresta] : g[vAtual])
        {
            int novoCusto = custoAtual + custoAresta;
            if (novoCusto < minDist[u])
                pq.push({novoCusto, u});
        }
    }
}

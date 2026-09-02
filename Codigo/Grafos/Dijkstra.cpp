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

	minDist[vInicial] = 0;
	pq.push({0, vInicial});

	while (!pq.empty())
	{
		// Extrai o vértice de menor custo
		auto [custoAtual, vAtual] = pq.top();
		pq.pop();

		// Se estamos em uma solução pior, ignoramos
		if (custoAtual > minDist[vAtual])
			continue;

		// Gera novas distâncias a partir dos vizinhos de vAtual
		for (auto [u, custoAresta] : g[vAtual])
		{
			int novoCusto = custoAtual + custoAresta;
			if (novoCusto < minDist[u])
			{
				minDist[u] = novoCusto;
				pq.push({novoCusto, u});
			}
		}
	}
}

// Dijkstra Quadrático
//
// Objetivo: calcular a menor distância de vInicial até cada vértice do grafo
// Retorna minDist, onde minDist[v] é essa distância, ou LINF se v for inalcançável
//
// Custo por execução: O(n²) de tempo, onde n é o número de vértices
// Memória: O(n) auxiliar e O(n²) para armazenar a matriz de adjacência
//
// Como funciona:
// 1. minDist começa com 0 para vInicial e LINF para os demais vértices
// 2. Buscamos linearmente o vértice não processado com menor minDist
// 3. Sua distância se torna definitiva: como ela é a menor disponível e todos
//    os pesos são positivos, nenhum caminho descoberto depois poderá melhorá-la
// 4. Percorremos sua linha na matriz e atualizamos cada aresta. Vemos se minDist[v] + peso(v, u) melhora minDist[u]
// 5. Repetimos até processar todos os vértices alcançáveis
//
// matAdj[u][v] guarda o peso da aresta de u para v, ou 0 se ela não existe
// Por isso, esta representação não permite arestas de peso 0
// Os vértices são 0-indexed


vector<vector<int>> matAdj;
vector<int> djikstraQuadratico(int vInicial, int nVertices)
{
	// minDist[v] é a melhor distância conhecida até v
	// vis[v] indica que essa distância já foi determinada definitivamente
	vector<int> minDist(nVertices, LINF);
	vector<bool> vis(nVertices, false);
	
	minDist[vInicial] = 0;
	
	for (int i = 0; i < nVertices; i++)
	{
		// Acha o vértice de menor distância, ainda não visitado.
		// Sabemos que a distância dele será miníma, pois usando qualquer outro vértice para chegar
		// nele resultaria em uma distância maior ainda (já que as arestas são sempre positivas)
		int minDistAtual = LINF, minV = -1;
		for (int v = 0; v < nVertices; v++)
		{
			if (!vis[v] && minDist[v] < minDistAtual)
			{
				minDistAtual = minDist[v];
				minV = v;
			}
		}

		// Se não existir, já sabemos a menor distância para todos os alcançáveis
		if (minV == -1) break;

		vis[minV] = true;

		for (int u = 0; u < nVertices; u++)
		{
			if (!matAdj[minV][u]) continue;

			// Utilizando esse novo vértice, existe um caminho mais curto?
			int novoCusto = minDist[minV] + matAdj[minV][u];
			minDist[u] = min(minDist[u], novoCusto);
		}
	}

	return minDist;
}

void solve() {
	int n, m, q; cin >> n >> m >> q;
	
	// O valor 0 representa a ausência de aresta
	matAdj = vector<vector<int>> (n, vector<int> (n, false));

	for (int i = 0; i < m; i++)
	{
		int u, v, c; cin >> u >> v >> c;
		u--, v--;

		// O grafo é não direcionado, então armazenamos a aresta nos dois sentidos
		if (matAdj[u][v] == 0)
    		matAdj[u][v] = matAdj[v][u] = c;

		// Caso existam múltiplas arestas, pegue a de peso mínimo
		else matAdj[u][v] = matAdj[v][u] = min(matAdj[u][v], c);
	}
}

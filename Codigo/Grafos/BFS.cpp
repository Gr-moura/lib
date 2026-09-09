#include <bits/stdc++.h>
using namespace std;

// BFS (busca em largura) em grafo
//
// Objetivo: calcular o menor número de arestas da origem até cada vértice alcançável.
//
// Tempo: O(V + E), onde V é o número de vértices e E o número de arestas.
// Memória: O(V + E) para o grafo e O(V) auxiliar para dist, pai e fila.
//
// g[v] contém os vizinhos de v; os vértices são numerados de 0 a V - 1.
// Em grafos não direcionados, adicione cada aresta nos dois sentidos.
// Preencha g antes de chamar BFS e use um vértice inicial válido.
// dist[v] guarda a menor distância; -1 indica um vértice inalcançável.
// pai[v] guarda de onde viemos ao descobrir v; a origem aponta para si mesma.
// pai[v] = -1 indica um vértice não descoberto.
// dist e pai são reinicializados a cada chamada.
//
//
// OBS.: Para gerar uma BFS com várias fontes (multisource): 
// Inicialize todas as origens com distância 0 e coloque cada uma
// na fila uma única vez, antes do while. O restante da busca permanece igual.
//
// dist[v] será a menor distância de qualquer origem até v, ainda em O(V + E).
// A mesma ideia vale para a BFS em grid, inicializando as células de origem.
// Faça pai[origem] = origem para cada fonte. A função path abaixo segue os pais
// até encontrar um vértice que aponta para si mesmo, identificando a origem do caminho.


vector<vector<int>> g;
vector<int> dist, pai;

void BFS(int vInicial)
{
	dist.assign(g.size(), -1);
	pai.assign(g.size(), -1);

	queue<int> q;
	dist[vInicial] = 0;
	pai[vInicial] = vInicial;
	q.push(vInicial);

	while (!q.empty())
	{
		int vAtual = q.front();
		q.pop();

		for (int u : g[vAtual])
		{
			// Tratamos dist != -1 como já visitado
			if (dist[u] != -1) continue;

			// Marcamos ao enfileirar para que cada vértice entre na fila apenas uma vez.
			dist[u] = dist[vAtual] + 1;
			pai[u] = vAtual;

			q.push(u);
		}
	}
}


// Reconstrução de um menor caminho
//
// Chame após BFS, usando um destino válido. Os pais determinam a origem do caminho.
// Retorna os vértices do caminho em ordem, incluindo origem e destino.
// Se o destino for inalcançável, retorna um vetor vazio.
// Se o destino for uma origem, retorna apenas esse vértice.
// Tempo e memória para o resultado: O(L), onde L é o número de vértices no caminho.


vector<int> path(int destino)
{
	if (dist[destino] == -1) return {};

	vector<int> caminho;
	int atual = destino;
	while (pai[atual] != atual)
	{
		caminho.push_back(atual);
		atual = pai[atual];
	}
	caminho.push_back(atual);

	// Seguimos os pais do destino à origem; invertemos para obter a ordem do percurso.
	reverse(caminho.begin(), caminho.end());
	return caminho;
}


// BFS (busca em largura) em grid
//
// Objetivo: calcular o menor número de movimentos da origem até cada célula alcançável.
// Como de cada vértice só podemos ir para cima, para baixo, para a direita e para a esquerda
// podemos usar um vetor de movimentos para gerar seus vizinhos.
//
// Tempo: O(n * m), onde n é o número de linhas e m o número de colunas.
// Cada célula entra na fila no máximo uma vez e tem até quatro vizinhos.
// Memória auxiliar: O(n * m) para distGrid e fila.
//
// Defina n e m antes da chamada e use uma célula inicial válida.
// x representa a linha e y a coluna, com índices começando em 0.
// distGrid guarda as menores distâncias; -1 indica células não alcançadas.
// Neste exemplo, todas as células dentro dos limites são livres.

using pii = pair<int, int>;

int n, m;
vector<vector<int>> distGrid;

// Cima, baixo, esquerda e direita
const vector<pii> movimentos = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

// Função para ver se uma nova posição na BFS é válida
bool val(int i, int j)
{
	if (i < 0 or i >= n) return false;
	if (j < 0 or j >= m) return false;

	return true;
}

void BFS_Grid(int xInicial, int yInicial)
{
	distGrid.assign(n, vector<int>(m, -1));

	queue<pii> q;
	distGrid[xInicial][yInicial] = 0;
	q.push({xInicial, yInicial});

	while (!q.empty())
	{
		auto [xAtual, yAtual] = q.front();
		q.pop();

		for (auto add : movimentos)
		{
			int xNovo = xAtual + add.first, yNovo = yAtual + add.second;
			if (!val(xNovo, yNovo) or distGrid[xNovo][yNovo] != -1) continue;

			// Marcamos ao enfileirar, evitando que outros vizinhos insiram a mesma célula.
			distGrid[xNovo][yNovo] = distGrid[xAtual][yAtual] + 1;
			q.push({xNovo, yNovo});
		}
	}
}

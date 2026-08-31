#include <bits/stdc++.h>
using namespace std;

// Lowest Common Ancestor (LCA)
//
// Pré-processa uma árvore enraizada no vértice 0 usando binary lifting e tempos
// de entrada e saída, permitindo encontrar o ancestral comum mais baixo de dois vértices
//
// O(n log(n)) de pré-processamento e memória; O(log(n)) por consulta de LCA,
// distância ou k-ésimo ancestral, onde n é o número de vértices
//
// A árvore deve estar em adj, com vértices no intervalo [0, numVertices), antes de
// chamar buildBL(). dist(a, b) retorna a distância em arestas e kthAncestor(k, a)
// requer 0 <= k <= depth[a]

int MAX_VERTICES = 2e5 + 10;
int LOG_MAX_VERTICES = 30; 
int numVertices, tempo;
vector<vector<int>> adj(MAX_VERTICES);

// anc[k][v] é o ancestral 2^k níveis acima de v
vector<vector<int>> anc(LOG_MAX_VERTICES, vector<int>(MAX_VERTICES, 0));
vector<int> in(MAX_VERTICES), out(MAX_VERTICES), sz(MAX_VERTICES), depth(MAX_VERTICES, -1);


void dfs(int vAtual, int vPai) // O(n)
{
    in[vAtual] = tempo++;

	if (vPai != -1) depth[vAtual] = 1 + depth[vPai];

    for (int u : adj[vAtual])
    {
        if (u != vPai)
        {
			// vAtual é o ancestral imediato de u: um salto de 2^0 = 1 aresta
            anc[0][u] = vAtual;
            dfs(u, vAtual);
        }
    }

    out[vAtual] = tempo++;

    // Cada vértice da subárvore contribui com um tempo de entrada e um de saída, por isso, dividimos por dois
	// Adicionamos +1 para poder incluir o nó atual no tamanho da árvore
	sz[vAtual] = (out[vAtual] + 1 - in[vAtual]) / 2;
}

void buildBL() // O(n log(n))
{
    tempo = 0;
    depth[0] = 0;

    // Enraíza a árvore em 0 e calcula tempos, profundidades e ancestrais imediatos
    dfs(0, -1);

    for (int k = 1; k < LOG_MAX_VERTICES; k++)
    {
        for (int i = 0; i < numVertices; i++)
        {
			// O oitavo ancestral de i é o quarto ancestral do quarto ancestral de i
			// Então, subimos 2^(k-1) níveis duas vezes para obter o ancestral 2^k
			anc[k][i] = anc[k - 1][anc[k - 1][i]];
        }
    }
}

bool isAncestor(int a, int b) // O(1)
{
    // O intervalo DFS de um ancestral contém todo o intervalo de seus descendentes
	// Já que seu tempo de entrada vem antes e, o de saída, depois
    if (in[a] <= in[b] and out[a] >= out[b]) return true;
    return false;
}

int LCA(int a, int b) // O(log(n))
{
    // Se um dos vértices já é ancestral do outro, ele próprio é o LCA
    if (isAncestor(a, b)) return a;
    if (isAncestor(b, a)) return b;

    // Fazemos uma busca binária no caminho de a até a raiz.
	// Procuramos o ancestral mais alto de a que ainda não é ancestral de b;
	// esse vértice estará imediatamente abaixo do LCA
	for (int k = LOG_MAX_VERTICES - 1; k >= 0; k--)
	{
		// Se o salto chegar ao LCA ou passar acima dele, não o realizamos
		if (isAncestor(anc[k][a], b)) continue;

		// O salto continua abaixo do LCA, então é seguro realizá-lo
		a = anc[k][a];
	}

    // O pai de a é o primeiro ancestral que também contém b em sua subárvore
    return anc[0][a];
}

int dist(int a, int b) // O(log(n))
{
    // Remove duas vezes o caminho compartilhado entre a raiz e o LCA
    return depth[a] + depth[b] - 2 * depth[LCA(a, b)];
}

int kthAncestor(int k, int a) // O(log(n))
{
    // Decompõe k em potências de dois e usa os saltos pré-calculados
    for (int i = LOG_MAX_VERTICES - 1; i >= 0; i--)
    {
        if (k & (1ULL << i)) a = anc[i][a];
    }

    return a;
}

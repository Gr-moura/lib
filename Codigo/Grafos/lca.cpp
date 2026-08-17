#include <bits/stdc++.h>
using namespace std;

int MAX_VERTICES = 2e5 + 10;
int LOG_MAX_VERTICES = 30; 
int numVertices, tempo;
vector<vector<int>> adj(MAX_VERTICES), anc(LOG_MAX_VERTICES, vector<int>(MAX_VERTICES, 0));
vector<int> in(MAX_VERTICES), out(MAX_VERTICES), sz(MAX_VERTICES), depth(MAX_VERTICES, -1);

void dfs(int vAtual, int vPai) // O(N)
{
    in[vAtual] = tempo++;

	if (vPai != -1) depth[vAtual] = 1 + depth[vPai];

    for (int u : adj[vAtual])
    {
        if (u != vPai)
        {
            anc[0][u] = vAtual;
            dfs(u, vAtual);
        }
    }

    out[vAtual] = tempo++;
	sz[vAtual] = (out[vAtual] - in[vAtual] + 1) / 2;
}

void buildBL() // O(NlogN)
{
    tempo = 0;
	depth[0] = 0;
    dfs(0, -1);

    for (int k = 1; k < LOG_MAX_VERTICES; k++)
    {
        for (int i = 0; i < numVertices; i++)
        {
			// O oitavo ancestral de i é o quarto ancestral do quarto ancestral de i
            anc[k][i] = anc[k - 1][anc[k - 1][i]];
        }
    }
}

bool isAncestor(int a, int b) // O(1)
{
	// Um vértice a é ancestral de b se o tempo de entrada de a for menor ou igual ao 
	// tempo de entrada de b e o tempo de saída de a for maior ou igual ao tempo de saída de b
    
	if (in[a] <= in[b] and out[a] >= out[b]) return true;
    return false;
}

int LCA(int a, int b) // O(NlogN)
{
    if (isAncestor(a, b)) return a;
    if (isAncestor(b, a)) return b;

	// Pegamos o maior ancestral de a que não é ancestral de b
    for (int k = LOG_MAX_VERTICES - 1; k >= 0; k--)
    {
        if (isAncestor(anc[k][a], b)) continue;
        a = anc[k][a];
    }

    return anc[0][a];
}

int dist(int a, int b) // O (NlogN)
{
	return depth[a] + depth[b] - 2 * depth[LCA(a, b)];
}

int kthAncestor(int k, int a) // O(NlogN)
{
	// Se o bit i de k for 1, subimos para o 2^i-ésimo ancestral de a
	for (int i = LOG_MAX_VERTICES - 1; i >= 0; i--)
	{
		if (k & (1ULL << i)) a = anc[i][a];
	}

	return a;
}

#include <bits/stdc++.h>
using namespace std;

// Maximum Clique
// Encontra o maior clique em um grafo não direcionado
// O(n * 2^(n/2)), onde n é o número de vértices do grafo
// Utiliza a técnica de meet-in-the-middle combinada com programação dinâmica
//
// Para encontrar o maior Conjunto Independente, basta rodar o algoritmo no grafo complemento
// Retorna a quantidade de vértices no maior clique e a máscara representando o clique

using ull = unsigned long long;

bool isBitSet(ull mask, ull bit)
{
    return (mask & (1ULL << bit)) != 0;
}

bool isSubset(ull subset, ull set)
{
    return (subset & set) == subset;
}

bool isClique(ull mask, ull start, ull end, const vector<ull> &adj)
{
    for (ull i = start; i <= end; i++)
    {
        if (!isBitSet(mask, i)) continue;

        // Vê se os outros bits ligados são um subconjunto dos adjacentes de i
        if (!isSubset(mask, adj[i])) return false;
    }

    return true;
}

pair<int, ull> maxClique(ull n, vector<ull> &adj)
{
    // Adiciona self-loops para facilitar a verificação de cliques
    for (int i = 0; i < n; i++)
        adj[i] |= (1ULL << i);

    ull mid = n / 2;
    ull leftSize = mid;
    ull rightSize = n - mid;

    // DP: memo[mask] armazena o melhor clique contido na máscara 'mask'
    vector<ull> memo(1ULL << leftSize);

    memo[0] = 0; // Clique vazio
    for (ull i = 1; i < (1ULL << leftSize); i++)
    {
        // Se o próprio conjunto i é um clique, ele é o melhor candidato base
        if (isClique(i, 0, mid - 1, adj))
        {
            memo[i] = i;
            continue;
        }

        // Se não é clique, a solução é a melhor solução dos subconjuntos
        // Recorrência: dp[mask] = max(dp[mask ^ (1 << j)]) para todo j setado
        ull bestSub = 0;
        for (ull j = 0; j < leftSize; j++)
        {
            if (isBitSet(i, j))
            {
                // Como a máscara (i ^ (1 << j)) é menor que i, ela já foi processada
                bestSub = max(bestSub, memo[i ^ (1ULL << j)]);
            }
        }

        memo[i] = bestSub;
    }

    ull globalBest = 0;

    // Meet-in-the-middle: Itera todos os subsets da direita
    // Intervalo [mid, n-1]
    for (ull i = 0; i < (1ULL << rightSize); i++)
    {
        ull rightPart = (i << mid);

        // Verifica se a parte da direita é válida sozinha
        if (!isClique(rightPart, mid, n - 1, adj)) continue;

        // Calcula quais nós da esquerda são compatíveis com TODOS os nós escolhidos na direita
        ull compativeisEsq = (1ULL << mid) - 1; // Máscara cheia da esquerda

        for (ull v = mid; v < n; v++)
        {
            if (isBitSet(rightPart, v))
            {
                // Intersecta com os adjacentes de v
                compativeisEsq &= adj[v];
            }
        }

        // Recupera o melhor clique possível na esquerda compatível com a direita
        ull leftPart = memo[compativeisEsq];
        ull candidate = rightPart | leftPart;

        if (__builtin_popcountll(candidate) > __builtin_popcountll(globalBest)) globalBest = candidate;
    }

    return {__builtin_popcountll(globalBest), globalBest};
}

void criarGrafoComplemento(int n, int m)
{
    vector<ull> adj(n, ~0ULL); // Inicializa grafo complemento (todas arestas existem exceto os conflitos)

    for (ull i = 0; i < m; i++)
    {
        ull u, v;
        cin >> u >> v;

        // Remove aresta entre u e v
        adj[u] &= ~(1ULL << v);
        adj[v] &= ~(1ULL << u);
    }
}
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

/* Seja 0 <= i < m e 0 <= j < n

Se tivermos uma DP da forma:
dp[i][j] = min{ dp[i - 1][k - 1] + Custo(k, j) },

onde 0 <= k <= j e o custo satisfaz a propriedade de quadrangle inequality, ou seja:
Custo(a, c) + Custo(b, d) <= Custo(a, d) + Custo(b, c) para a <= b <= c <= d

Então podemos otimizar o cálculo da DP usando a técnica de Divide and Conquer DP,
que reduz a complexidade de O(m * n^2) para O(m * n log n).
*/

const int maxM = 1000, maxN = 1000;
ll dp[maxM][maxN]; // dp[i][j] representa o custo mínimo para a i-ésima etapa e j-ésimo estado

ll Custo(int k, int j)
{
    // Função de custo fictícia, deve ser substituída pela função real
    return abs(j - k);
}

void compute(int etapaAtual, int l, int r, int optLB, int optUB)
{
    if (l > r) return;

    int mid = (l + r) / 2;
    pair<long long, int> best = {LLONG_MAX, -1};

    for (int k = optLB; k <= min(mid, optUB); ++k)
    {
        ll cost = (k ? dp[etapaAtual - 1][k - 1] : 0) + Custo(k, mid);
        if (cost < best.first) best = {cost, k};
    }

    dp[etapaAtual][mid] = best.first;
    int optMid = best.second;

    compute(etapaAtual, l, mid - 1, optLB, optMid);
    compute(etapaAtual, mid + 1, r, optMid, optUB);
}

void divideAndConquerDP(int m, int n)
{
    // Inicialização da primeira linha da DP, caso base
    for (int j = 0; j < n; ++j)
    {
        dp[0][j] = Custo(0, j); // Custo inicial fictício
    }

    for (int i = 1; i < m; ++i)
    {
        compute(i, 0, n - 1, 0, n - 1);
    }
}

// Podemos também aplicar uma técnica semelhante a um sliding window para calcular o custo de forma eficiente
// quando o custo depende de uma subarray [l, r], ajustando os ponteiros lAtual e rAtual para expandir ou contrair a
// janela e atualizando o custo incrementalmente.

// Assim, temos uma complexidade amortizada eficiente para calcular Custo(k, j),
// uma vez que, em um mesmo nível de DP, o ponteiro R se move no máximo 2 * n vezes e o ponteiro L também se move no
// máximo 2 * n vezes.
int lAtual = 0, rAtual = -1;
int custo = 0;

int arr[maxN];
int qt[maxN];

// Substitua a função de custo por essa função de resize
int resize(int l, int r)
{
    while (lAtual > l)
    {
        lAtual--;

        // Atualiza o custo ao expandir a janela para a esquerda
        // Exemplo fictício de atualização do custo
        qt[arr[lAtual]]++;
        custo += qt[arr[lAtual]] - 1;
    }

    while (rAtual < r)
    {
        rAtual++;

        qt[arr[rAtual]]++;
        custo += qt[arr[rAtual]] - 1;
    }

    while (lAtual < l)
    {
        custo -= qt[arr[lAtual]] - 1;
        qt[arr[lAtual]]--;

        lAtual++;
    }

    while (rAtual > r)
    {
        custo -= qt[arr[rAtual]] - 1;
        qt[arr[rAtual]]--;
        rAtual--;
    }

    return custo;
}

// Given sequences A & B, compute LCS(A, B)
// Subproblems: L(i, j) = LCS ( A[i:] & B[j:] ), for 0 <= i <= |A| & 0 <= j <= |B|
// Relate: L(i, j) = 1 + L(i + 1, j + 1), if A[i] == B[j]
// L(i, j) = max { L(i + 1, j), L(i, j + 1) }, otherwise
// Top. Order: for i = |A|, ..., 0, for j = |B|, ..., 0
// Base: L(|A|, j) = 0, L(i, |B|) = 0, for all 0 <= i <= |A| & 0 <= j <= |B|
// Original Problem: L(0, 0)
// Time: O(|A| * |B|)

#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e3 + 10;
typedef pair<int, int> pii;

enum DIR { NONE, DIAG, DOWN, RIGHT };

string A, B;
vector<vector<int>> memo (MAX, vector<int>(MAX, -1));
vector<vector<DIR>> parent (MAX, vector<DIR>(MAX, NONE));

int dp(int i, int j)
{
	if (memo[i][j] != -1) return memo[i][j];
	if (i == A.size() || j == B.size()) return 0;

	if (A[i] == B[j])
		return memo[i][j] = 1 + dp(i + 1, j + 1);
		
	return memo[i][j] = max(dp(i + 1, j), dp(i, j + 1));
}


int dpPai(int i, int j)
{
    // Retorna valor já computado (evita recomputação)
    if (memo[i][j] != -1) return memo[i][j];

    // Caso base: uma das sequências acabou, LCS é 0
    if (i == A.size() || j == B.size()) return memo[i][j] = 0;

    if (A[i] == B[j])
    {
        // Caractere em comum: pertence ao LCS, avança nas duas sequências
        parent[i][j] = DIAG;
        return memo[i][j] = 1 + dpPai(i + 1, j + 1);
    }

    // Sem match: toma o melhor entre pular em A ou pular em B
    memo[i][j] = max(dpPai(i + 1, j), dpPai(i, j + 1));

    // Detecta qual ramo gerou o máximo
    parent[i][j] = (memo[i][j] == dpPai(i + 1, j)) ? DOWN : RIGHT;
    return memo[i][j];
}

string reconstruir()
{
    string lcs;

	dpPai(0, 0); // Preenche a tabela de memoização e a tabela de pais
    int i = 0, j = 0;

    // Para quando alguma sequência se esgota
    while (parent[i][j] != NONE)
    {
		// Se o próximo passo é diagonal, significa que A[i] == B[j] e faz parte do LCS
		if (parent[i][j] == DIAG)
		{
			lcs += A[i]; // ou B[j], ambos são iguais
			i++, j++;
			continue;
		}

		// Atualiza as coordenadas com base na direção
		else if (parent[i][j] == DOWN) i++;
		else j++;
    }

    return lcs;
}
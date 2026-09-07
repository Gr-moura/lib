#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

// Busca completa com next_permutation
//
// Objetivo: gerar todas as permutações distintas em ordem lexicográfica
//
// Tempo: O(n * P), onde n é o tamanho da string e P é o número de permutações distintas.
// Se cada caractere tem frequência fi, P = n! / (f1! * f2! * ...).
// No pior caso, todos os caracteres são diferentes e P = n!.
//
// Caracteres repetidos não geram saídas duplicadas;
// Exemplo: aab -> aba -> baa.
// Sem a ordenação inicial, as permutações menores que a string inicial seriam omitidas.
void solve()
{
	string s; cin >> s;

	// Começa pela menor permutação para garantir que todas sejam visitadas.
	sort(s.begin(), s.end());

	do
	{
		// Processa a permutação atual; aqui, apenas imprimimos a string.
		cout << s << endl;
} while (next_permutation(s.begin(), s.end()));
}

// Busca completa com prev_permutation
//
// Objetivo: gerar todas as permutações distintas em ordem lexicográfica decrescente
// Tempo: O(n * P), assim como no exemplo com next_permutation.
//
// Começamos pela maior permutação e usamos prev_permutation para obter a anterior.
// Quando não há anterior, retorna false e restaura a maior permutação.
// Caracteres repetidos não geram saídas duplicadas.
// Exemplo: baa -> aba -> aab.
// Sem a ordenação decrescente inicial, as permutações maiores seriam omitidas.

void solvePrevPermutation()
{
	string s; cin >> s;

	// Ordenar pelos iteradores reversos deixa a string em ordem decrescente.
	sort(s.rbegin(), s.rend());

	do
	{
		// Processa a permutação atual antes de tentar obter a anterior.
		cout << s << endl;
	} while (prev_permutation(s.begin(), s.end()));
}

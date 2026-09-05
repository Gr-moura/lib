#include <bits/stdc++.h>
using namespace std;

// Contagem de Inversões
//
// Uma inversão é um par de índices (i, j) tal que i < j e nums[i] > nums[j]
//
// O(n log n) de tempo, onde n é o número de elementos do vetor
// O(n) de memória auxiliar
//
// A contagem é feita durante o Merge Sort. Quando um elemento da metade esquerda
// é maior que o elemento atual da direita, todos os elementos seguintes a ele na parte esquerda
// também formarão uma inversão com o atual da direita

// Junta dois vetores ordenados e retorna o resultado e a quantidade de inversões
pair<vector<int>, long long> merge(const vector<int> &esq, const vector<int> &dir)
{
	int n1 = esq.size(), n2 = dir.size();

	vector<int> ord;
	int idxEsq = 0, idxDir = 0;
	long long inv = 0;

	// Escolhe o menor elemento disponível entre os dois vetores
	while (idxEsq < n1 && idxDir < n2)
	{
		if (esq[idxEsq] <= dir[idxDir]) ord.push_back(esq[idxEsq++]);
		else
		{
			ord.push_back(dir[idxDir++]);

			// O atual e todos os seguintes, do lado esquerdo, também formam uma inversão com esse da direita
			inv += n1 - idxEsq;
		}
	}

	// Copia os elementos restantes do vetor que ainda não terminou
	while (idxEsq < n1) ord.push_back(esq[idxEsq++]);
	while (idxDir < n2) ord.push_back(dir[idxDir++]);

	return {ord, inv};
}

// Retorna o vetor ordenado e sua quantidade de inversões
pair<vector<int>, long long> mergeSort(const vector<int> &nums)
{
	int n = nums.size();

	// Vetores com zero ou um elemento já estão ordenados
	if (n <= 1) return {nums, 0};

	// Divide o vetor em duas metades
	int mid = n / 2;
	vector<int> esq(nums.begin(), nums.begin() + mid);
	vector<int> dir(nums.begin() + mid, nums.end());

	// Ordena cada metade e conta suas inversões
	auto [ordEsq, invEsq] = mergeSort(esq);
	auto [ordDir, invDir] = mergeSort(dir);

	// Junta as duas metades e conta as inversões entre elas
	auto [ord, invMerge] = merge(ordEsq, ordDir);
	return {ord, invEsq + invDir + invMerge};
}

long long countInversions(const vector<int> &nums)
{
	return mergeSort(nums).second;
}

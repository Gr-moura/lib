#include <bits/stdc++.h>
using namespace std;

// Merge Sort
//
// Retorna uma cópia ordenada do vetor em ordem não decrescente
//
// O(n log n) de tempo, onde n é o número de elementos do vetor
// O(n) de memória auxiliar
//
// Como funciona:
// 1. Divide o vetor atual em duas metades
// 2. Ordena cada metade recursivamente
// 3. Junta as metades ordenadas em um novo vetor
//
// O algoritmo é estável: elementos iguais mantêm sua ordem relativa original

// Junta dois vetores ordenados e retorna o resultado
vector<int> merge(const vector<int> &esq, const vector<int> &dir)
{
	int n1 = esq.size(), n2 = dir.size();

	vector<int> ord;
	int idxEsq = 0, idxDir = 0;

	// Escolhe o menor elemento disponível entre os dois vetores
	while (idxEsq < n1 && idxDir < n2)
	{
		if (esq[idxEsq] <= dir[idxDir]) ord.push_back(esq[idxEsq++]);
		else ord.push_back(dir[idxDir++]);
	}

	// Copia os elementos restantes do vetor que ainda não terminou
	while (idxEsq < n1) ord.push_back(esq[idxEsq++]);
	while (idxDir < n2) ord.push_back(dir[idxDir++]);

	return ord;
}

vector<int> mergeSort(const vector<int> &nums)
{
	int n = nums.size();

	// Vetores com zero ou um elemento já estão ordenados
	if (n <= 1) return nums;

	// Divide o vetor em duas metades
	int mid = n / 2;
	vector<int> esq(nums.begin(), nums.begin() + mid);
	vector<int> dir(nums.begin() + mid, nums.end());

	// Ordena cada metade separadamente
	esq = mergeSort(esq);
	dir = mergeSort(dir);

	// Junta as duas metades e retorna o vetor ordenado
	return merge(esq, dir);
}

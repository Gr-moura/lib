// Dado um conjunto de pontos, o Convex Hull (envoltória convexa)
// é o menor polígono convexo que contém todos os pontos.

// Um polígono convexo é um polígono tal que qualquer segmento que conecta
// dois vértices está inteiramente contido no polígono

#include <bits/stdc++.h>
#include "Ponto.cpp"
using namespace std;

// Convex Hull - Monotone Chain (Andrew) Algorithm - O(n log n)
vector<pt> convexHull(vector<pt> pontos)
{
	if (pontos.size() <= 1) return pontos;
 
	// Ordena os pontos por coordenada x
	sort(pontos.begin(), pontos.end());

	// Remove pontos duplicados
	pontos.erase(unique(pontos.begin(), pontos.end()), pontos.end());

	// Constrói a metade inferior do hull
	vector<pt> lowerHull;
	for (int i = 0; i < pontos.size(); i++) 
	{
		// Se p[-2] -> p[-1] -> pAtual NÃO for um giro estrito à esquerda, 
		// então o ponto p[-1] é interior ou colinear e pode ser descartado.
		while (lowerHull.size() > 1 and !isCCW(lowerHull.end()[-2], lowerHull.end()[-1], pontos[i]))
			lowerHull.pop_back();
	
		lowerHull.push_back(pontos[i]);
	}

	// Constrói a metade superior do hull
	vector<pt> upperHull;
	for (int i = pontos.size() - 1; i >= 0; i--) 
	{
		// Se p[-2] -> p[-1] -> pAtual NÃO for um giro estrito à esquerda, 
		// então o ponto p[-1] é interior ou colinear e pode ser descartado.
		while (upperHull.size() > 1 and !isCCW(upperHull.end()[-2], upperHull.end()[-1], pontos[i]))
			upperHull.pop_back();
		
		upperHull.push_back(pontos[i]);
	}

	// Remove os pontos finais de cada metade para evitar duplicação
	lowerHull.pop_back(); upperHull.pop_back();

	// Concatena o lower hull com o upper hull
	for (pt i : upperHull) lowerHull.push_back(i);

	return lowerHull;
}
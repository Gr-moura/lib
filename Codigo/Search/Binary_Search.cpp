#include <bits/stdc++.h>
using namespace std;

// Busca binária: retorna o primeiro valor de [l, r] para o qual pos é true.
// Requer l <= r, pos(r) == true e pos no formato false ... false, true ... true.
// Tempo: O(C * log(W)), com W candidatos e custo C por chamada de pos.
// Memória auxiliar: O(1)


using ll = long long;

ll alvo;

bool pos(ll valor)
{
	// Adapte esta condição e os dados necessários conforme o exercício.
	return valor >= alvo;
}

ll binarySearch(ll l, ll r)
{
	while (l < r)
	{
		ll mid = l + (r - l) / 2;

		// A resposta permanece em [l, r]: mid válido ainda pode ser o primeiro.
		if (pos(mid)) r = mid;
		else l = mid + 1;
	}

	return l;
}

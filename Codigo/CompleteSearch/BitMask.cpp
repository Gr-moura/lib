#include <bits/stdc++.h>
using namespace std;

// Busca completa com bitmask
//
// Objetivo: Realizar todas as possíveis divisões de n elementos em 2 grupos
//
// Tempo: O(n * 2^n), pois testamos 2^n máscaras e percorremos cada uma delas (tamanho n)
// Memória auxiliar: O(1), pois os grupos não são armazenados
// Esses custos consideram apenas a enumeração; a lógica adicionada pode aumentá-los.
//
// Como funciona:
// 1. Cada máscara representa uma escolha de quais elementos pertencem ao grupo A
// 2. Se o bit i está ligado, o elemento de índice i vai para A; caso contrário, vai para B
//
// São 2^n divisões com A e B distintos e permitindo grupos vazios.
// Se trocar A por B representar a mesma solução, cada divisão é visitada duas vezes
// para n > 0.
//
// Requisito: 0 <= n < 63 para usar 1LL << n.
// Na prática, o custo exponencial exige n bem menor (por exemplo, n <= 20).

void solve()
{
	int n;
	cin >> n;

	// Há 2^n subconjuntos de n elementos, representados pelas máscaras de 0 a 2^n - 1.
	for (long long bitMask = 0; bitMask < (1LL << n); bitMask++)
	{
		for (int bitAtual = 0; bitAtual < n; bitAtual++)
		{
			// 1LL << bitAtual cria uma máscara com apenas esse bit ligado.
			// O operador & verifica se ele também está ligado em bitMask.
			if (bitMask & (1LL << bitAtual))
			{
				// O elemento atual vai para A
			}

			else
			{
				// O elemento atual vai para B
			}
		}
		// Calcula algo dado o grupo
	
	}
}

#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;

const ull LOG_ME = 30; // Máxima quantidade de bits (log MAX_ELEMENT) - D

ull basis[LOG_ME];
ull szBasis = 0;

void insertVector(ull mask) // O(D)
{
    for (int i = LOG_ME - 1; i >= 0; i--)
    {
        if ((mask & (1ULL << i)) == 0) continue; // O bit atual está desligado, fazemos nada

        if (!basis[i]) // Não temos ninguém controlando o bit atual
        {
            basis[i] = mask, szBasis++; // adicionamos como base
            return;
        }

        mask ^= basis[i]; // Subtraímos a base que já temos (XOR em Zd2 = adição = subtração)
    }
}

ull max_XORsum() // O(D)
{
    ull retorno = 0;
    for (int i = LOG_ME - 1; i >= 0; i--)
    {
        if (retorno & (1ULL << i)) continue; // Se o bit atual já está ligado, fazemos nada
        if (!basis[i]) continue;             // Se não temos como modificar o bit atual, fazemos nada

        retorno ^= basis[i]; // Ativamos o bit atual
    }

    return retorno;
}

ull findKthLargest_XORsum(ull kth, ull valorBase = 0) // O(D)
{
    ull retorno = valorBase;
    ull l = 1, r = 1ULL << szBasis;
    for (int i = LOG_ME - 1; i >= 0; i--)
    {
        if (!basis[i]) continue; // Não podemos fazer nada

        ull mid = l + (r - l) / 2;
        if (kth <= mid) // Temos de desativar esse bit
        {
            r = mid;

            if ((retorno & (1ULL << i)) == 0) continue;
            else retorno ^= basis[i];
        }

        else // Temos de ativar esse bit
        {
            l = mid + 1;

            if (retorno & (1ULL << i)) continue;
            else retorno ^= basis[i];
        }
    }

    return retorno;
}

ull bestLEQ(ull k, ull valorBase = 0) // O(D^2)
{
    ull ans = 0;
    if (valorBase <= k) ans = valorBase; // O valor base é uma possibilidade?

    int l = 1, r = 1ULL << szBasis;
    while (l <= r)
    {
        int mid = l + (r - l) / 2;
        ull res = findKthLargest_XORsum(mid, valorBase);

        if (res == k) return res; // Achamos uma solucão ótima

        else if (res < k) // Menor que nosso objetivo
        {
            l = mid + 1;
            ans = max(ans, res);
        }

        else r = mid - 1; // Maior que nosso objetivo
    }

    return ans;
}
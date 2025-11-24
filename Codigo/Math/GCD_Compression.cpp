#include <bits/stdc++.h>
using namespace std;

// Suponha que você tenha um conjunto de números em que você adiciona elementos um por um e em cada etapa calcula o GCD
// de todos os números do conjunto. Então, não teremos mais do que log max(ai) valores diferentes de GCD. Assim, você
// pode manter informações compactadas sobre todos os GCDs em subsegmentos de ai:
// O (n log ^2 max(ai))

// Key: um valor distinto de GCD
// Value: o maior length L, tal que existe um subsegmento de comprimento L que termina na posição i e cujo GCD é Key
// gcd(a[i-L], a[i-L+1], ..., a[i]) = Key

const int n = 1e5; // tamanho máximo do array
int a[n];          // array de entrada

// sub_gcd[i]: mapa que armazena os GCDs distintos dos subarrays que terminam em a[i]
map<int, int> sub_gcd[n];

void compressGCD(int length)
{
    // O único subarrary que termina em a[0] é o próprio a[0] e tem GCD igual a a[0]
    sub_gcd[0][a[0]] = 1;

    for (int i = 1; i < length; i++)
    {
        // Adiciona o subarray que contém apenas a[i] como possível GCD
        sub_gcd[i][a[i]] = 1;

        // Atualiza os GCDs dos subarrays anteriores
        for (auto &[gcdAnterior, len] : sub_gcd[i - 1])
        {
            // Recalcula considerando que estamos terminando em a[i]
            int newGCD = gcd(gcdAnterior, a[i]);

            // Diferentes subarrays, quando extendidos até a[i], podem resultar no mesmo GCD
            // Então usamos max/min para decidir qual comprimento armazenar
            sub_gcd[i][newGCD] = max(sub_gcd[i][newGCD], len + 1);
        }
    }
}
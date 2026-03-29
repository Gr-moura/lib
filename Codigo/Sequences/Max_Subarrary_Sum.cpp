#include <bits/stdc++.h>
using namespace std;

// Algoritmo de Kadane para encontrar a soma máxima de um subarray contínuo
// O(n), onde n é o tamanho do array
//
// Para encontrar a Min Subarray Sum, basta inverter os sinais dos elementos do array e
// depois inverter o resultado final

int maxSubarraySum(const vector<int> &a)
{
    int n = a.size();

    int ans = a[0], somaAtual = 0;

    for (int r = 0; r < n; r++)
    {
        somaAtual += a[r];
        ans = max(ans, somaAtual);

        // Nunca vale a pena continuar com uma soma negativa
        if (somaAtual < 0) somaAtual = 0;
    }

    return ans;
}

// Soma máxima, [índice inicial, índice final]
pair<int, pair<int, int>> maxSubarraySumInd(const vector<int> &a)
{
    int n = a.size();
    int ans = a[0], ansL = 0, ansR = 0;
    int somaAtual = 0, minus_pos = -1;

    for (int r = 0; r < n; r++)
    {
        somaAtual += a[r];
        if (somaAtual > ans)
        {
            ans = somaAtual;

            // Começo do subarray é a posição após a última vez que a soma foi negativa
            ansL = minus_pos + 1;
            ansR = r;
        }

        // Nunca vale a pena continuar com uma soma negativa
        if (somaAtual < 0)
        {
            somaAtual = 0;

            // Última posição onde a soma atual foi negativa
            minus_pos = r;
        }
    }

    return {ans, {ansL, ansR}};
}

int maxCircularSubarraySum(const vector<int> &a)
{
    int n = a.size();

    // Caso 1: O subarray máximo não é circular
    int ans = maxSubarraySum(a);

    // Soma de todos os elementos do array
    int total = accumulate(a.begin(), a.end(), 0);

    // Caso 2: O subarray começa no final e termina no início do array
    // Se o subarray máximo é circular, os elementos que não pertencem a ele
    // também formam uma parte contínua. Assim, podemos maximizar a soma
    // circular minimizando a soma dos elementos que não pertencem ao subarray.

    // Inverte os sinais dos elementos do array
    vector<int> aInv(n);
    for (int i = 0; i < n; i++)
        aInv[i] = -a[i];

    // Soma mínima do array original é igual à soma máxima do array invertido
    int minSubarraySum = maxSubarraySum(aInv);

    // Subarray máximo circular é igual à soma total menos a soma mínima
    int circularSum = total + minSubarraySum; // minSubarraySum é negativo

    // Se todos os elementos são negativos, circularSum será 0
    if (ans < 0) return ans;
    return max(ans, circularSum);
}
#include <bits/stdc++.h>
using namespace std;

// Acha o k-ésimo menor elemento em arr entre os índices [left, right]
// O(n) espaço extra, O(n) tempo esperado, O(n^2) tempo no pior caso

// A biblioteca <algorithm> possui a função nth_element que implementa o QuickSelect de forma + eficiente, onde o tempo
// no pior caso é O(n log n)
int quickSelect(vector<int> &arr, int k)
{
    int n = arr.size();
    if (k < 1 || k > n) return INT_MAX; // k inválido

    int pivotIndex = rand() % n;
    int pivotValue = arr[pivotIndex];

    vector<int> A1, A2;
    for (int i = 0; i < n; ++i)
    {
        // Adiciona elementos menores que o pivô em A1 e maiores em A2
        if (arr[i] < pivotValue) A1.push_back(arr[i]);
        else if (arr[i] > pivotValue) A2.push_back(arr[i]);
    }

    if (k <= A1.size()) return quickSelect(A1, k);                           // Está na pilha dos elementos menores
    else if (k > n - A2.size()) return quickSelect(A2, k - (n - A2.size())); // Está na pilha dos elementos maiores
    else return pivotValue;                                                  // É igual ao pivô
}
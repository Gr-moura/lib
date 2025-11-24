#include <bits/stdc++.h>
using namespace std;

int medianOfMedians(vector<int> &arr, int left, int right, int k);
int partition(vector<int> &arr, int left, int right, int pivot)
{
    int pivotValue = arr[pivot];
    swap(arr[pivot], arr[right]);
    int storeIndex = left;

    for (int i = left; i < right; ++i)
    {
        if (arr[i] < pivotValue)
        {
            swap(arr[storeIndex], arr[i]);
            ++storeIndex;
        }
    }

    swap(arr[storeIndex], arr[right]);
    return storeIndex;
}

int medianOfMedians(vector<int> &arr, int left, int right, int k)
{
    if (k > 0 && k <= right - left + 1)
    {
        int n = right - left + 1;
        vector<int> medians((n + 4) / 5);
        for (int i = 0; i < n / 5; ++i)
        {
            sort(arr.begin() + left + i * 5, arr.begin() + left + i * 5 + 5);
            medians[i] = arr[left + i * 5 + 2];
        }

        if (i * 5 < n)
        {
            sort(arr.begin() + left + i * 5, arr.begin() + left + i * 5 + n % 5);
            medians[i] = arr[left + i * 5 + n % 5 / 2];
            ++i;
        }

        int medOfMed = (i == 1) ? medians[0] : medianOfMedians(medians, 0, i - 1, i / 2);

        int pivotIndex = find(arr.begin() + left, arr.begin() + right + 1, medOfMed) - arr.begin();
        pivotIndex = partition(arr, left, right, pivotIndex);

        if (pivotIndex - left == k - 1) return arr[pivotIndex];
        if (pivotIndex - left > k - 1) return medianOfMedians(arr, left, pivotIndex - 1, k);

        return medianOfMedians(arr, pivotIndex + 1, right, k - pivotIndex + left - 1);
    }

    return INT_MAX;
}
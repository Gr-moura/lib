// Given sequence S, compute LIS(S)
// Subproblems: L(i) = LIS ( S[i:] ), that starts with S[i]
// Relate: L(i) = 1 + max { L(j) | i < j < |S| and S[i] < S[j] }
// Top. Order: for i = |S| - 1, ..., 0
// Base: L(|S|) = 0
// Original Problem: max { L(i) | 0 <= i < |S| }
// Time: O(|S|^2)

#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e3 + 10;

vector<int> S;
vector<int> memo (MAX, -1);

int dp(int i)
{
	if (memo[i] != -1) return memo[i];
	if (i == S.size()) return 0;

	int maxLen = 1;
	for (int j = i + 1; j < S.size(); j++)
		if (S[i] < S[j])
			maxLen = max(maxLen, 1 + dp(j));

	return memo[i] = maxLen;
}


// Given DAG G & vertex s, compute minDist(v), for all v e V
// Subproblems: minDist(v), for each v e V
// Relate: minDist(v) = min { minDist(u) + w (u, v) | u e adj-(v) } U { LINF }
// Top. Order: Topological Order of DAG G
// Base: minDist(s) = 0
// Original Problem: All subproblems
// Time: O(|V| + |E|)

// This can very easily be adapted to compute the longest path in a DAG,
// just by changing the minDist to maxDist and LINF to -LINF.

#include <bits/stdc++.h>
using namespace std;

const int MAX = 2e5 + 10;
typedef pair<int, int> pii;
const int LINF = 0x3f3f3f3f;

vector<int> memo (MAX, -1);
vector<vector<pii>> g(MAX);

int dp(int vAtual)
{
	if (memo[vAtual] != -1) return memo[vAtual];
	if (vAtual == 0) return 0;

	int minDist = LINF;
	for (auto [u, w]: g[vAtual])
		minDist = min(minDist, dp(u) + w);

	return memo[vAtual] = minDist;
}

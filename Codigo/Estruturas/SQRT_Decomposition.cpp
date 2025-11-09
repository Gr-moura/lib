#include <bits/stdc++.h>
using namespace std;

struct Sqrt // O(n) para criar
{
    int block_size;
    vector<int> nums;
    vector<long long> blocks;
    Sqrt(int sqrtn, vector<int> &arr) : block_size(sqrtn), blocks(sqrtn, 0)
    {
        nums = arr;
        for (int i = 0; i < nums.size(); i++)
        {
            blocks[i / block_size] += nums[i];
        }
    }

    // O(1) update to set nums[x] to v
    void update(int x, int v)
    {
        blocks[x / block_size] -= nums[x];
        nums[x] = v;
        blocks[x / block_size] += nums[x];
    }

    // O(sqrt(n)) query for sum of [0, r)
    long long query(int r)
    {
        long long res = 0;
        for (int i = 0; i < r / block_size; i++)
        {
            res += blocks[i];
        }
        for (int i = (r / block_size) * block_size; i < r; i++)
        {
            res += nums[i];
        }
        return res;
    }

    // O(sqrt(n)) query for sum of [l, r)
    long long query(int l, int r) { return query(r) - query(l - 1); }
};

// Mo's algorithm
void remove(idx); // TODO: remove value at idx from data structure
void add(idx);    // TODO: add value at idx from data structure
int get_answer(); // TODO: extract the current answer of the data structure

int BLOCK_SIZE;

// Hilbert order calculation optimization
inline int64_t hilbertOrder(int x, int y, int pow, int rotate);

struct Query
{
    int l, r, idx;
    int ord;

    // // Ao invés de 21, escolha o menor k tal que 2^k >= tamanho máximo do array
    // Query(int _l, int _r, int _idx) : l(_l), r(_r), idx(_idx) { ord = hilbertOrder(l, r, 21, 0); }
    // bool operator<(Query &other) const { return ord < other.ord; }

    bool operator<(const Query &other) const
    {
        if (l / BLOCK_SIZE != other.l / BLOCK_SIZE) return l < other.l;

        // Se o bloco for par, ordena r de forma crescente, se for ímpar, de forma decrescente
        // Isso gera uma espécie de percurso em zigue-zague, reduzindo o número de operações add/remove
        return ((l / BLOCK_SIZE) & 1) ? (r > other.r) : (r < other.r);
    }
};

vector<int> mo_s_algorithm(vector<Query> &queries)
{
    vector<int> answers(queries.size());
    sort(queries.begin(), queries.end());

    // TODO: initialize data structure

    int cur_l = 0, cur_r = -1;
    // invariant: data structure will always reflect the range [cur_l, cur_r]
    for (Query &q : queries)
    {
        while (cur_l > q.l)
        {
            cur_l--;
            add(cur_l);
        }
        while (cur_r < q.r)
        {
            cur_r++;
            add(cur_r);
        }
        while (cur_l < q.l)
        {
            remove(cur_l);
            cur_l++;
        }
        while (cur_r > q.r)
        {
            remove(cur_r);
            cur_r--;
        }
        answers[q.idx] = get_answer();
    }
    return answers;
}

inline int64_t hilbertOrder(int x, int y, int pow, int rotate)
{
    if (pow == 0)
    {
        return 0;
    }
    int hpow = 1 << (pow - 1);
    int seg = (x < hpow) ? ((y < hpow) ? 0 : 3) : ((y < hpow) ? 1 : 2);
    seg = (seg + rotate) & 3;
    const int rotateDelta[4] = {3, 0, 0, 1};
    int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
    int nrot = (rotate + rotateDelta[seg]) & 3;
    int64_t subSquareSize = int64_t(1) << (2 * pow - 2);
    int64_t ans = seg * subSquareSize;
    int64_t add = hilbertOrder(nx, ny, pow - 1, nrot);
    ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
    return ans;
}
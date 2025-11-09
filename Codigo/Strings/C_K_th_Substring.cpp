/*
ID: gabriel139
LANG: C++
TASK: test
*/

/* clang-format off */
#include <bits/stdc++.h>
using namespace std;

#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }

void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
	cerr << *it << " = " << a << endl;
	err(++it, args...);
}

#define rep(i, begin, end) for (__typeof(end) i = (begin) - ((begin) > (end)); i != (end) - ((begin) > (end)); i += 1 - 2 * ((begin) > (end)))

#define dbg(x) cout << #x << " = " << x << endl
#define printv(a) {for(auto u:a) cout<<u<<" "; cout<<endl;}
#define all(x) x.begin(), x.end()
#define int long long
#define endl '\n'
#define f first
#define s second
#define pb push_back
#define eb emplace_back
#define lb(vect, x) (lower_bound(all(vect), x) - vect.begin())
#define ub(vect, x) (upper_bound(all(vect), x) - vect.begin())

typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

void NO() { cout << "NO" << endl; }
void YES() { cout << "YES" << endl; }

bool prime(ll a) { if (a <= 1) return 0; if (a == 2) return 1; if (a % 2 == 0) return 0; for (int i = 3; i*i <= a; i+=2) if (a % i == 0) return 0; return 1; }

const int MOD = 1e9 + 7, MAX = 1e4 + 10;
const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;
/* clang-format on */

struct SuffixAutomaton // O(n log k) para criar
{
    struct state
    {
        int len, link;
        map<char, int> next;
    };

    state st[MAX * 2];
    int sz = 0, last = 0;

    void extend(char c)
    {
        int cur = sz++;
        st[cur].len = st[last].len + 1;

        int p = last;
        while (p != -1 && !st[p].next.count(c)) // Adicionamos c aos sufixos antigos
        {
            st[p].next[c] = cur;
            p = st[p].link;
        }

        if (p == -1) // Não existia nenhum utilizando c antes
        {
            // Como é a primeira vez, o único sufixo existente é a string vazia
            st[cur].link = 0;
            last = cur;

            return;
        }

        int q = st[p].next[c];
        if (st[p].len + 1 == st[q].len)
        {
            st[cur].link = q;
            last = cur;

            return;
        }

        // Transição não contínua - Criamos um clone
        int clone = sz++;
        st[clone].len = st[p].len + 1;
        st[clone].next = st[q].next;
        st[clone].link = st[q].link;
        while (p != -1 && st[p].next[c] == q)
        {
            st[p].next[c] = clone;
            p = st[p].link;
        }
        st[q].link = st[cur].link = clone;

        last = cur;
    }

    SuffixAutomaton() // Cria estado inicial (string vazia)
    {
        st[0].len = 0, st[0].link = -1;
        sz++, last = 0;
    }

    SuffixAutomaton(string &s) // Já cria ele completo O(n log k)
    {
        st[0].len = 0, st[0].link = -1;
        sz++, last = 0;

        for (auto c : s)
            extend(c);
    }

    int qt[MAX * 2];
    int qtStringsSaindo(int estadoAtual = 0)
    {
        int ans = 1;
        for (auto [c, w] : st[estadoAtual].next)
            ans += qtStringsSaindo(w);

        return qt[estadoAtual] = ans;
    }

    string kesimaString(int k, int posAtual = 0, string ans = "", int estadoAtual = 0)
    {
        for (auto [c, proximoEstado] : st[estadoAtual].next)
        {
            int qtd = qtStringsSaindo(proximoEstado);

            posAtual++; // Quando adicionamos um caractere, vamos para uma posicao a mais na ordem
            if (posAtual == k) return ans + c;

            // se a k-ésima substring está dentro das substrings do filho
            if (posAtual + (qtd - 1) >= k) return kesimaString(k, posAtual, ans + c, proximoEstado);

            // senão, pula todas as substrings do filho
            posAtual += qtd - 1;
        }

        return ans;
    }
};

void solve()
{
    string s;
    cin >> s;

    SuffixAutomaton sam(s);

    int n;
    cin >> n;

    cout << sam.kesimaString(n) << endl;
}

int32_t main()
{
    // freopen("test.in", "r", stdin);
    // freopen("test.out", "w", stdout);

    // casas decimais
    // cout << fixed << setprecision(1);

    // horario
    // cout << setfill('0') << setw(2);

    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t = 1;
    // cin >> t;

    for (int i = 1; i <= t; i++)
    {
        solve();

        // #ifdef ONPC
        //         cout << "__________________________" << endl;
        // #endif
    }

    return 0;
}

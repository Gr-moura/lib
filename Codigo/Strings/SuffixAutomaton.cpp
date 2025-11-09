// Suffix Automaton
//
// AFD que comprime todas as substrings de uma string
#include <bits/stdc++.h>
using namespace std;
const int MAX = 100000;

// Suffix Automaton
//
// AFD que comprime todas as substrings de uma string

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

    bool isPresent(string &s); // O(|S| log k)
    int qtDiffStrings();       // O(n)
    int szAllSubstrings();     // O(n)
    int qtStringsSaindo(int estadoAtual = 0);
};

bool SuffixAutomaton::isPresent(string &s) // O(|S| log k)
{
    int estadoAtual = 0;
    for (auto c : s)
    {
        if (!st[estadoAtual].next.count(c)) return false; // Não existe a transição
        estadoAtual = st[estadoAtual].next[c];
    }

    return true;
}

int qtDiffStrings() // O(n)
{
    // Uma substring aparece apenas em um estado,
    // basta somar a qt substrings em cada estado

    int tot = 0;
    for (int i = 1; i < sz; i++)
        tot += st[i].len - st[st[i].link].len;

    return tot;
}

int szAllSubstrings() // O(n)
{
    int tot = 0;
    for (int i = 1; i < sz; i++)
    {
        int shortest = st[st[i].link].len + 1; // minLen(v) = 1 + maxLen(link(v))
        int longest = st[i].len;

        int num_strings = longest - shortest + 1;
        int cur = num_strings * (longest + shortest) / 2; // Sn = (a1 + an) * n/2

        tot += cur;
    }
    return tot;
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
}
;
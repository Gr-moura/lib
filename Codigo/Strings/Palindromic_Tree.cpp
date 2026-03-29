const int maxn = 1e5, sigma = 26;

int s[maxn], len[maxn], link[maxn], to[maxn][sigma];

int n, last, sz;

void init()
{
    s[n++] = -1;
    link[0] = 1;
    len[1] = -1;
    sz = 2;
}

int get_link(int v)
{
    while (s[n - len[v] - 2] != s[n - 1])
        v = link[v];
    return v;
}

void add_letter(int c)
{
    s[n++] = c;
    last = get_link(last);
    if (!to[last][c])
    {
        len[sz] = len[last] + 2;
        link[sz] = to[get_link(link[last])][c];
        to[last][c] = sz++;
    }
    last = to[last][c];
}

#include <iostream>
#include <map>
#include <string>
#include <vector>

class PalindromicTreeRollback
{
  private:
    struct Node
    {
        int len;
        int link;
        int quick_link; // [cite: 201] Otimização para garantir O(log N) no add/pop
        std::map<char, int> next;

        Node(int l = 0, int lnk = 0, int qlnk = 0) : len(l), link(lnk), quick_link(qlnk) {}
    };

    // Estrutura para armazenar o histórico de operações para o rollback
    struct HistoryState
    {
        int previous_last;      // O valor de 'last' antes do add
        int created_node_index; // Índice do nó criado (-1 se nenhum foi criado)
        int parent_node;        // Nó pai onde a aresta foi adicionada
        char char_added;        // Caractere adicionado
    };

    std::vector<Node> nodes;
    std::vector<HistoryState> history;
    std::string s;
    int last;

  public:
    PalindromicTreeRollback()
    {
        nodes.reserve(100000);

        // Setup das raízes (0: par, 1: ímpar)
        // quick_link da raiz par (0) aponta para raiz ímpar (1) por convenção base
        nodes.emplace_back(0, 1, 1);
        // quick_link da raiz ímpar (1) aponta para si mesma ou base (0) para evitar loops infinitos na lógica
        nodes.emplace_back(-1, 0, 0);

        last = 0;
        s.push_back('#'); // Sentinela
    }

    // Navegação otimizada usando Quick Links [cite: 211-214]
    int get_link(int v) const
    {
        int pos = s.size() - 1;
        while (true)
        {
            int len_v = nodes[v].len;
            // Se o palíndromo v pode ser estendido (s[pos - len - 1] == s[pos]), encontramos.
            if (pos - 1 - len_v >= 0 && s[pos - 1 - len_v] == s[pos])
            {
                break;
            }

            // Otimização Quick Link:
            // Se o caractere que invalida v é o mesmo que invalida link[v],
            // podemos pular todos os intermediários diretamente para quick_link.
            if (nodes[v].link > 1 && s[pos - 1 - nodes[nodes[v].link].len] != s[pos])
            {
                v = nodes[v].quick_link;
            }
            else
            {
                v = nodes[v].link;
            }

            // Segurança de borda para raízes
            if (v == 1) return 1;
            if (v == 0 && nodes[v].len == 0) return 1; // Fallback extremo
        }
        return v;
    }

    // Adiciona caractere com suporte a rollback
    void add(char c)
    {
        s.push_back(c);
        int cur = get_link(last);

        HistoryState state;
        state.previous_last = last;
        state.created_node_index = -1; // Default: nenhum nó criado
        state.char_added = c;
        state.parent_node = cur;

        if (nodes[cur].next.find(c) == nodes[cur].next.end())
        {
            int len = nodes[cur].len + 2;
            int link = (len == 1) ? 0 : nodes[get_link(nodes[cur].link)].next[c];

            // Cálculo do Quick Link para o novo nó [cite: 207-209]
            // Se o caractere que precede o sufixo (link) é o mesmo que precede
            // o sufixo do sufixo (link[link]), copiamos o quick_link.
            int qlink = 0;
            if (link > 1)
            {
                int pos = s.size() - 1;
                // Verificamos s[pos - len[link]] vs s[pos - len[link[link]]]
                // Note que 'pos' é o final do novo palíndromo.
                // O caractere anterior ao link é s[pos - nodes[link].len].
                // Mas aqui estamos definindo a estrutura estática.
                // A definição do paper depende dos caracteres dentro da string armazenada no nó.

                // Implementação prática simplificada do paper:
                // quickLink[v] = (s[v.end - link[v].len] == s[v.end - link[link[v]].len]) ? quickLink[link[v]] :
                // link[link[v]]

                // Como não armazenamos a string explicitamente no nó, usamos a string global 's'
                // O novo nó termina em s.size()-1.
                int idx_link_pre = (int)s.size() - 1 - nodes[link].len;
                int idx_link_link_pre = (int)s.size() - 1 - nodes[nodes[link].link].len;

                if (idx_link_pre >= 0 && idx_link_link_pre >= 0 && s[idx_link_pre] == s[idx_link_link_pre])
                {
                    qlink = nodes[link].quick_link;
                }
                else
                {
                    qlink = nodes[nodes[link].link].len == -1 ? 1 : nodes[link].link;
                    // Se o link do link for a raiz ímpar (-1), apontamos para 1 (root odd) ou 0 (root even)
                }
            }
            else
            {
                qlink = 0; // Fallback seguro para nós pequenos
            }

            nodes.emplace_back(len, link, qlink);
            state.created_node_index = nodes.size() - 1;
            nodes[cur].next[c] = state.created_node_index;
        }

        last = nodes[cur].next[c];
        history.push_back(state);
    }

    // Remove o último caractere e restaura a árvore [cite: 252]
    void pop()
    {
        if (history.empty()) return;

        HistoryState state = history.back();
        history.pop_back();

        // 1. Restaura o ponteiro 'last'
        last = state.previous_last;

        // 2. Se um nó foi criado, removemos ele
        if (state.created_node_index != -1)
        {
            // Remove a aresta do pai
            nodes[state.parent_node].next.erase(state.char_added);

            // Remove o nó do vetor.
            // NOTA: Isso só é seguro se o nó criado for EXATAMENTE o último do vetor.
            // Em uma estrutura de pilha pura (add/pop LIFO), isso é sempre verdade.
            nodes.pop_back();
        }

        // 3. Remove o caractere da string buffer
        s.pop_back();
    }

    // Retorna o tamanho do maior sufixo palíndromo atual
    int get_max_suf_len() const { return nodes[last].len; }

    int size() const
    {
        return nodes.size() - 2; // Desconsidera as duas raízes
    }
};
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

// Red-black tree do PBDS.
// insert, erase, find, lower_bound, upper_bound e consultas de ordem: O(log n).
// Memoria: O(n).
//
// Parametros de tree<Key, Mapped, Cmp, Tag, Node_Update, Allocator>:
// - Key: tipo da chave (int, long long, pair, string, ...).
// - Mapped: null_type para set; um tipo como string para map.
// - Cmp: less<Key> crescente; greater<Key> decrescente; ou comparador proprio.
//   Deve definir uma ordem estrita fraca. NAO use less_equal para repetidos!
// - Tag: rb_tree_tag escolhe a red-black tree balanceada.
//   Alternativas: splay_tree_tag (splay) e ov_tree_tag (vetor ordenado,
//   com insercao linear). Os custos acima se referem a rb_tree_tag.
// - Node_Update: tree_order_statistics_node_update guarda tamanhos de subarvores
//   e habilita find_by_order/order_of_key. null_node_update nao oferece isso.

template <class Key, class Cmp = less<Key>>
using ordered_set = tree<Key, null_type, Cmp, rb_tree_tag,
                         tree_order_statistics_node_update>;

template <class Key, class Value, class Cmp = less<Key>>
using ordered_map = tree<Key, Value, Cmp, rb_tree_tag,
                         tree_order_statistics_node_update>;

/*
Operacoes (ordered_set<Key> s, ordem crescente):

insert(x)       => Insere x sem duplicar; retorna {iterador, inseriu}.
erase(x)        => Remove x; retorna true se removeu, false se nao existia.
erase(it)       => Remove o elemento do iterador; retorna o proximo iterador.
find(x)         => Iterador para x, ou end() se nao existir.
lower_bound(x)  => Iterador para o primeiro elemento >= x, ou end().
upper_bound(x)  => Iterador para o primeiro elemento > x, ou end().
find_by_order(k)=> Iterador para o k-esimo menor (base 0), ou end() se k >= size().
order_of_key(x) => Quantidade de elementos < x; x nao precisa existir.
size()          => Quantidade de elementos. O(1).
empty()         => true se a arvore estiver vazia. O(1).
begin()         => Iterador para o menor elemento. O(1).
end()           => Sentinela depois do ultimo elemento; nao e um elemento. O(1).
rbegin()        => Iterador reverso para o maior elemento. O(1).
rend()          => Sentinela que encerra a iteracao reversa. O(1).
clear()         => Remove todos os elementos. O(n).

As operacoes de insert ate order_of_key custam O(log n).
Nunca desreferencie end()/rend(); k deve ser nao negativo.
*it acessa o elemento; ++it/--it percorrem a ordem. Percurso completo: O(n).
Para posicao/rank, use find_by_order/order_of_key (next/distance sao lineares).

Ordem decrescente: ordered_set<int, greater<int>> s;

find_by_order(k) => Iterador para o k-esimo MAIOR, base 0.
order_of_key(x)  => Quantidade de elementos > x.
lower_bound(x)   => Iterador para o primeiro elemento <= x, ou end().
upper_bound(x)   => Iterador para o primeiro elemento < x, ou end().
begin()/rbegin() => Maior/menor elemento, respectivamente.

Map: ordered_map<int, int> mp; (ordem e rank pelas CHAVES)

mp[x]           => Referencia ao valor de x; se ausente, insere com valor 0.
                   Para outros tipos, usa Value() (ex.: string vazia).
insert({x, v})  => Insere chave/valor; se x existir, conserva o valor anterior.
find(x)         => Iterador para o par chave/valor, ou end(); nao insere.
find_by_order(k)=> Iterador para o par com a k-esima menor chave.
it->first       => Chave (nao pode ser alterada pelo iterador).
it->second      => Valor associado (pode ser alterado).

Repetidos: ordered_set<pair<int, long long>> s;
Use (valor, id_unico), com 0 <= id < LLONG_MAX. Nao use less_equal!

insert({x, id})                  => Insere uma ocorrencia de x.
erase({x, id})                   => Remove essa ocorrencia especifica.
find_by_order(k)->first          => Valor da k-esima ocorrencia, base 0.
order_of_key({x, -1})            => Quantidade de valores < x.
order_of_key({x, LLONG_MAX})      => Quantidade de valores <= x.
lower_bound({x, -1})             => Primeira ocorrencia com valor >= x, ou end().

// Remover uma copia de x, se existir:
auto it = s.lower_bound({x, -1});
if (it != s.end() && it->first == x) s.erase(it);

// Contar ocorrencias de x sem calcular x + 1 (evita overflow):
auto qtd = s.order_of_key({x, LLONG_MAX}) - s.order_of_key({x, -1});
*/

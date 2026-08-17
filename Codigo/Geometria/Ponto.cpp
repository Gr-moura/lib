// Geometria - inteiro
#include <bits/stdc++.h>
using namespace std;

#define sq(x) ((x)*(ll)(x))
typedef long long ll;

struct pt 
{
	ll x, y;
	pt(ll x_ = 0, ll y_ = 0) : x(x_), y(y_) {}

	bool operator < (const pt ot) const {
		if (x != ot.x) return x < ot.x;
		return y < ot.y;
	}

	bool operator == (const pt ot) const {
		return x == ot.x and y == ot.y;
	}

	pt operator + (const pt ot) const { return pt(x + ot.x, y + ot.y); }
	pt operator - (const pt ot) const { return pt(x - ot.x, y - ot.y); }
	pt operator * (const ll c) const { return pt(x * c, y * c); }

	// Considere theta o menor ângulo entre os vetores A e B, então:

	// Produto Escalar (Dot Product): |A| * |B| * cos(theta)
    // Retorna: módulo de A vezes a projeção de B em A.
    // > 0: mesmo sentido (ângulo agudo).
    // < 0: sentidos opostos (ângulo obtuso).
    // == 0: vetores perpendiculares.
    ll operator * (const pt ot) const { 
        return x * ot.x + y * ot.y; 
    }
    
    // Produto Vetorial 2D (Cross Product / Determinante): |A| * |B| * sen(theta)
    // Retorna: área orientada do paralelogramo formado por A e B.
    // > 0: vetor B está à esquerda de A (sentido anti-horário).
    // < 0: vetor B está à direita de A (sentido horário).
    // == 0: vetores paralelos / colineares.
    ll operator ^ (const pt ot) const { 
        return x * ot.y - y * ot.x; 
    }
	
	friend istream& operator >> (istream& in, pt& p) {
		return in >> p.x >> p.y;
	}
};

bool isPerpendicular(pt a, pt b){
	return a * b == 0;
}

bool isParalelo(pt a, pt b){
	return a ^ b == 0;
}

// Calcula o quadrado da distância euclidiana entre os pontos P e Q.
ll dist2(pt p, pt q) {
	return sq(p.x - q.x) + sq(p.y - q.y);
}

// Calcula o dobro da área com sinal do triângulo formado pelos pontos P, Q e R.
ll sarea2(pt p, pt q, pt r) {
	return (q - p) ^ (r - q);
}

bool isColinear(pt p, pt q, pt r){ 
	return sarea2(p, q, r) == 0;
}

// 1: vetor B está à esquerda de A (sentido anti-horário).
// -1: vetor B está à direita de A (sentido horário).
// 0: vetores paralelos / colineares.
int direction(pt a, pt b, pt o = pt(0, 0))
{
	ll pVetorial = (a - o) ^ (b - o);
	if (pVetorial > 0) return 1; // sentido anti-horário
	if (pVetorial < 0) return -1; // sentido horário
	return 0; // colinear
}

// Avalia se o caminho P -> Q -> R, ou seja, PQ com QR, constitui uma curva para a esquerda (Counter-Clockwise).
bool isCCW(pt p, pt q, pt r) { // O(1)
	return sarea2(p, q, r) > 0;
}

// Retorna em qual quadrante um ponto está
int quad(pt p) 
{
	if (p.x >= 0 and p.y >= 0) return 0; // Superior Direito
	if (p.x < 0 and p.y >= 0) return 1; // Superior Esquerdo
	if (p.x < 0 and p.y < 0) return 2; // Inferior Esquerdo
	if (p.x >= 0 and p.y < 0) return 3; // Inferior Direito
}




// RETA

bool isinseg(pt p, line r) { // se p pertence ao seg de r
	pt a = r.p - p, b = r.q - p;
	return (a ^ b) == 0 and (a * b) <= 0;
}

bool interseg(line r, line s) { // se o seg de r intersecta o seg de s
	if (isinseg(r.p, s) or isinseg(r.q, s)
		or isinseg(s.p, r) or isinseg(s.q, r)) return 1;

	return ccw(r.p, r.q, s.p) != ccw(r.p, r.q, s.q) and
			ccw(s.p, s.q, r.p) != ccw(s.p, s.q, r.q);
}

int segpoints(line r) { // numero de pontos inteiros no segmento
	return 1 + __gcd(abs(r.p.x - r.q.x), abs(r.p.y - r.q.y));
}

double get_t(pt v, line r) { // retorna t tal que t*v pertence a reta r
	return (r.p^r.q) / (double) ((r.p-r.q)^v);
}

// POLIGONO

// quadrado da distancia entre os retangulos a e b (lados paralelos aos eixos)
// assume que ta representado (inferior esquerdo, superior direito)
ll dist2_rect(pair<pt, pt> a, pair<pt, pt> b) {
	int hor = 0, vert = 0;
	if (a.second.x < b.first.x) hor = b.first.x - a.second.x;
	else if (b.second.x < a.first.x) hor = a.first.x - b.second.x;
	if (a.second.y < b.first.y) vert = b.first.y - a.second.y;
	else if (b.second.y < a.first.y) vert = a.first.y - b.second.y;
	return sq(hor) + sq(vert);
}

ll polarea2(vector<pt> v) { // 2 * area do poligono
	ll ret = 0;
	for (int i = 0; i < v.size(); i++)
		ret += sarea2(pt(0, 0), v[i], v[(i + 1) % v.size()]);
	return abs(ret);
}

// se o ponto ta dentro do poligono: retorna 0 se ta fora,
// 1 se ta no interior e 2 se ta na borda
int inpol(vector<pt>& v, pt p) { // O(n)
	int qt = 0;
	for (int i = 0; i < v.size(); i++) {
		if (p == v[i]) return 2;
		int j = (i+1)%v.size();
		if (p.y == v[i].y and p.y == v[j].y) {
			if ((v[i]-p)*(v[j]-p) <= 0) return 2;
			continue;
		}
		bool baixo = v[i].y < p.y;
		if (baixo == (v[j].y < p.y)) continue;
		auto t = (p-v[i])^(v[j]-v[i]);
		if (!t) return 2;
		if (baixo == (t > 0)) qt += baixo ? 1 : -1;
	}
	return qt != 0;
}

ll interior_points(vector<pt> v) { // pontos inteiros dentro de um poligono simples
	ll b = 0;
	for (int i = 0; i < v.size(); i++)
		b += segpoints(line(v[i], v[(i+1)%v.size()])) - 1;
	return (polarea2(v) - b) / 2 + 1;
}

struct convex_pol {
	vector<pt> pol;

	// nao pode ter ponto colinear no convex hull
	convex_pol() {}
	convex_pol(vector<pt> v) : pol(convex_hull(v)) {}

	// se o ponto ta dentro do hull - O(log(n))
	bool is_inside(pt p) {
		if (pol.size() == 0) return false;
		if (pol.size() == 1) return p == pol[0];
		int l = 1, r = pol.size();
		while (l < r) {
			int m = (l+r)/2;
			if (ccw(p, pol[0], pol[m])) l = m+1;
			else r = m;
		}
		if (l == 1) return isinseg(p, line(pol[0], pol[1]));
		if (l == pol.size()) return false;
		return !ccw(p, pol[l], pol[l-1]);
	}
	// ponto extremo em relacao a cmp(p, q) = p mais extremo q
	// (copiado de https://github.com/gustavoM32/caderno-zika)
	int extreme(const function<bool(pt, pt)>& cmp) {
		int n = pol.size();
		auto extr = [&](int i, bool& cur_dir) {
			cur_dir = cmp(pol[(i+1)%n], pol[i]);
			return !cur_dir and !cmp(pol[(i+n-1)%n], pol[i]);
		};
		bool last_dir, cur_dir;
		if (extr(0, last_dir)) return 0;
		int l = 0, r = n;
		while (l+1 < r) {
			int m = (l+r)/2;
			if (extr(m, cur_dir)) return m;
			bool rel_dir = cmp(pol[m], pol[l]);
			if ((!last_dir and cur_dir) or
					(last_dir == cur_dir and rel_dir == cur_dir)) {
				l = m;
				last_dir = cur_dir;
			} else r = m;
		}
		return l;
	}
	int max_dot(pt v) {
		return extreme([&](pt p, pt q) { return p*v > q*v; });
	}
	pair<int, int> tangents(pt p) {
		auto L = [&](pt q, pt r) { return ccw(p, r, q); };
		auto R = [&](pt q, pt r) { return ccw(p, q, r); };
		return {extreme(L), extreme(R)};
	}
};

bool operator <(const line& a, const line& b) { // comparador pra reta
	// assume que as retas tem p < q
	pt v1 = a.q - a.p, v2 = b.q - b.p;
	bool b1 = compare_angle(v1, v2), b2 = compare_angle(v2, v1);
	if (b1 or b2) return b1;
	return ccw(a.p, a.q, b.p); // mesmo angulo
}
bool operator ==(const line& a, const line& b) {
	return !(a < b) and !(b < a);
}

// comparador pro set pra fazer sweep line com segmentos
struct cmp_sweepline {
	bool operator () (const line& a, const line& b) const {
		// assume que os segmentos tem p < q
		if (a.p == b.p) return ccw(a.p, a.q, b.q);
		if (a.p.x != a.q.x and (b.p.x == b.q.x or a.p.x < b.p.x))
			return ccw(a.p, a.q, b.p);
		return ccw(a.p, b.q, b.p);
	}
};

// comparador pro set pra fazer sweep angle com segmentos
pt dir;
struct cmp_sweepangle {
    bool operator () (const line& a, const line& b) const {
        return get_t(dir, a) < get_t(dir, b);
    }
};
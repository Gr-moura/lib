// Aritmetica Modular
//
// O mod tem q ser primo

template <int p> struct mod_int
{
    // Exponenciacao rapida
    // (b^e mod p) em O(log(e))
    ll expo(ll b, ll e)
    {
        ll ret = 1;
        while (e)
        {
            if (e % 2) ret = ret * b % p;
            e /= 2, b = b * b % p;
        }
        return ret;
    }

    // Inverso modular de b mod p, onde p é primo
    ll inv(ll b) { return expo(b, p - 2); }

    using m = mod_int;
    int v;

    mod_int() : v(0) {}
    mod_int(ll v_)
    {
        if (v_ >= p or v_ <= -p) v_ %= p;
        if (v_ < 0) v_ += p;
        v = v_;
    }

    m &operator+=(const m &a)
    {
        v += a.v;
        if (v >= p) v -= p;
        return *this;
    }

    m &operator-=(const m &a)
    {
        v -= a.v;
        if (v < 0) v += p;
        return *this;
    }

    m &operator*=(const m &a)
    {
        v = v * ll(a.v) % p;
        return *this;
    }

    m &operator/=(const m &a)
    {
        v = v * inv(a.v) % p;
        return *this;
    }

    m operator-() { return m(-v); }

    m &operator^=(ll e)
    {
        if (e < 0)
        {
            v = inv(v);
            e = -e;
        }
        v = expo(v, e);
        // possivel otimizacao:
        // cuidado com 0^0
        // v = expo(v, e%(p-1));
        return *this;
    }

    bool operator==(const m &a) { return v == a.v; }
    bool operator!=(const m &a) { return v != a.v; }

    friend istream &operator>>(istream &in, m &a)
    {
        ll val;
        in >> val;
        a = m(val);
        return in;
    }

    friend ostream &operator<<(ostream &out, m a) { return out << a.v; }
    friend m operator+(m a, m b) { return a += b; }
    friend m operator-(m a, m b) { return a -= b; }
    friend m operator*(m a, m b) { return a *= b; }
    friend m operator/(m a, m b) { return a /= b; }
    friend m operator^(m a, ll e) { return a ^= e; }
};

const int MOD = 1e9 + 7;
typedef mod_int<(int)MOD> mint;

// Caso queira algo mais simples
int binpow(int x, int y)
{
    int z = 1;
    while (y)
    {
        if (y & 1) z = mul(z, x);
        x = mul(x, x);
        y >>= 1;
    }
    return z;
}

int add(int x, int y)
{
    x += y;
    if (x >= MOD) x -= MOD;
    if (x < 0) x += MOD;
    return x;
}

int mul(int x, int y)
{
    return x * 1LL * y % MOD;
}

int divide(int x, int y)
{
    return mul(x, binpow(y, MOD - 2));
}

#include <cmath>
#include <cstdio>


#define MAXK 50


typedef unsigned long long u64;


template<typename T>
T gcd(T a, T b) { for (T c = a%b; c != 0; a=b,b=c,c=a%b); return b; }

template<typename TB, typename TE>
TB sq_pow(TB b, TE e) {
    TB res = 1; for (; e; e >>= 1, b *= b) if (e & 1) res *= b;
    return res;
}

struct U128 {
    u64 lo, hi;
    static const size_t sz  = 128;
    static const size_t hsz = 64;
    static const u64 bmax = -1;

    U128() : lo(0), hi(0) {}
    U128(int v) : lo(v), hi(0) {}

    U128 operator-() const { return ~U128(*this) + 1; }
    U128 operator~() const {
		U128 t(*this);
		t.lo = ~t.lo;
		t.hi = ~t.hi;
		return t;
	}

    U128 &operator+=(const U128 &b) {
        if (lo > bmax - b.lo) ++hi;
        lo += b.lo;
        hi += b.hi;
        return *this;
    }
    U128 &operator-=(const U128 &b) { return *this += -b; }
    U128 &operator*=(const U128 &b) {
        if (*this == 0 || b == 1) return *this;
        if (b == 0) { lo = hi = 0; return *this; }

        U128 a(*this);
        U128 t = b;

        lo = hi = 0;

        for (size_t i = 0; i < sz; ++i) {
            if((t & 1) != 0) *this += (a << i);
            t >>= 1;
        }
        return *this;
    }
    U128 &operator/=(const U128 &b) {
		U128 rem;
		divide(*this, b, *this, rem);
		return *this;
    }
    U128 &operator%=(const U128 &b) {
		U128 quo;
		divide(*this, b, quo, *this);
		return *this;
    }

    static void
    divide(const U128 &num, const U128 &den, U128 &quo, U128 &rem) {
        if(den == 0) { int a = 0; quo = U128(a/a); }
        U128 n = num, d = den, x = 1, ans = 0;

        while((n >= d) && (((d >> (sz - 1)) & 1) == 0)) {
            x <<= 1;
            d <<= 1;
        }

        while(x != 0) {
            if(n >= d) {
                n -= d;
                ans |= x;
            }

            x >>= 1;
            d >>= 1;
        }

        quo = ans, rem = n;
    }

    U128 &operator&=(const U128 &b) { hi &= b.hi; lo &= b.lo; return *this; }
    U128 &operator|=(const U128 &b) {
        hi |= b.hi;
        lo |= b.lo;
        return *this;
    }
    U128 &operator<<=(const U128& rhs) {
		size_t n = rhs.to_int();
        if (n >= sz) { lo = hi = 0; return *this; }

        if(n >= hsz) {
            n -= hsz;
            hi = lo;
            lo = 0;
        }

        if(n != 0) {
            hi <<= n;
            const u64 mask(~(u64(-1) >> n));
            hi |= (lo & mask) >> (hsz - n);
            lo <<= n;
        }

        return *this;
	}
    U128 &operator>>=(const U128& rhs) {
		size_t n = rhs.to_int();
        if (n >= sz) { lo = hi = 0; return *this; }

        if(n >= hsz) {
            n -= hsz;
            lo = hi;
            hi = 0;
        }

        if(n != 0) {
            lo >>= n;
            const u64 mask(~(u64(-1) << n));
            lo |= (hi & mask) << (hsz - n);
            hi >>= n;
        }

        return *this;
	}

    int to_int() const { return static_cast<int>(lo); }
    u64 to_u64() const { return lo; }

    bool operator==(const U128 &b) const { return hi == b.hi && lo == b.lo; }
    bool operator!=(const U128 &b) const { return !(*this == b); }
    bool operator<(const U128 &b) const {
        return (hi == b.hi) ? lo < b.lo : hi < b.hi; }
    bool operator>=(const U128 &b) const { return ! (*this < b); }
    U128 operator&(const U128 &b) const { U128 a(*this); return a &= b; }
    U128 operator<<(const U128 &b) const { U128 a(*this); return a <<= b; }
    U128 operator>>(const U128 &b) const { U128 a(*this); return a >>= b; }
    U128 operator*(const U128 &b) const { U128 a(*this); return a *= b; }
    U128 operator+(const U128 &b) const { U128 a(*this); return a += b; }
    U128 operator-(const U128 &b) const { U128 a(*this); return a -= b; }
    U128 operator%(const U128 &b) const { U128 a(*this); return a %= b; }
};

template<typename T>
struct Fraction {
    T p, q;

    Fraction() { p = 0, q = 1; }
    Fraction(T P, T Q) : p(P), q(Q) { simplify(); }
    void simplify() {
        T g = gcd(p, q);
        p /= g;
        q /= g;
    }
    Fraction operator+(const Fraction &f) const {
        return Fraction(p * f.q + q * f.p, q * f.q);
    }
    Fraction operator-(const Fraction &f) const {
        return Fraction(p * f.q - q * f.p, q * f.q);
    }
    Fraction operator*(const Fraction &f) const {
        return Fraction(p * f.p, q * f.q);
    }
    Fraction operator/(const Fraction &f) const {
        return Fraction(p * f.q, q * f.p);
    }
};


typedef Fraction<U128> Frac;

int k1, k2;
const Frac one(1, 1);


Frac solve(Frac &P)
{
    Frac Q = one - P;

    Frac Pk2(sq_pow(P.p, k2), sq_pow(P.q, k2));
    Frac Qk1(sq_pow(Q.p, k1), sq_pow(Q.q, k1));

    Frac Pk2Qk1 = Pk2*Qk1;

    return (one - Qk1 - Pk2 + Pk2Qk1) / (P*Qk1 + Pk2*Q - Pk2Qk1);
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        int p, q;
        scanf("%d%d%d%d", &p, &q, &k1, &k2);
        Frac P(p, q);
        Frac ans = solve(P);
        ans.simplify();

        printf("Case %d: ", ++ncase);

        u64 x = ans.p.to_u64();
        u64 y = ans.q.to_u64();
        printf("%llu / %llu\n", x, y);
    }

    return 0;
}

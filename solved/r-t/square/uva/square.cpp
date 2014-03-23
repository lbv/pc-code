#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
using namespace std;


#define MAXN 100

#define Zero(v) memset((v), 0, sizeof(v))


typedef long long i64;


#define IsComp(n)  (_c[n>>6]&(1<<((n>>1)&31)))
#define SetComp(n) _c[n>>6]|=(1<<((n>>1)&31))
const int MAXP   = 500;
const int SQRP   =  23;  // sqrt(MAX)
const int MAX_NP = 102;  // 1.26 * MAXP/log(MAXP)
int _c[(MAXP>>6)+1];
int primes[MAX_NP];
int pidx[MAXP];
int nprimes;
void prime_sieve() {
    for (int i = 3; i <= SQRP; i += 2)
        if (!IsComp(i)) for (int j = i*i; j <= MAXP; j+=i+i) SetComp(j);
    primes[nprimes++] = 2;
    for (int i=3; i <= MAXP; i+=2) if (!IsComp(i)) primes[nprimes++] = i;
    for (int i = 0; i < nprimes; ++i)
        pidx[primes[i]] = i;
}

struct Mod2 {
    int v;
    Mod2() {}
    Mod2(int V) : v(V) {}
    bool operator!=(const Mod2 &x) const { return v != x.v; }
    Mod2 operator/(const Mod2 &x) const { return Mod2(v); }
    Mod2 operator*(const Mod2 &x) const { return Mod2(v & x.v); }
    Mod2 &operator-=(const Mod2 &x) { v ^= x.v; return *this; }
};

const int MAX_ROWS = MAX_NP;
const int MAX_COLS = MAXN;

template <typename T>
struct Matrix {
    int r, c;
    T m[MAX_ROWS][MAX_COLS];
    Matrix() {}

    void clr() { Zero(m); }

    int gaussian() {
        int fv = 0, nr, p, q;
        for (p=0, q=0; p < r && q < c; ++p, ++q) {
            for (nr = p; nr < r; ++nr) if (m[nr][q] != 0) break;
            if (nr == r) { ++fv; --p; continue; }
            if (nr != p) swap(m[p], m[nr]);
            for (int i = p + 1; i < r; ++i) {
                T fac = m[i][q] / m[p][q];
                for (int j = q + 1; j < c; ++j)
                    m[i][j] -= m[p][j] * fac;
                m[i][q] = 0;
            }
        }
        return fv + c - q;
    }
};


Matrix<Mod2> A;

int n;


void process(i64 x, int c)
{
    int sx = sqrt(x);
    for (int i = 0; i < nprimes; ++i) {
        int &p = primes[i];
        if (p > sx) break;
        if (x % p != 0) continue;

        int e = 0;
        while (x % p == 0) x /= p, ++e;
        int pf = pidx[p];
        A.m[pf][c] = e % 2;
        sx = sqrt(x);
    }
    if (x > 1) {
        int pf = pidx[x];
        A.m[pf][c] = 1;
    }
}

i64 solve()
{
    A.r = nprimes, A.c = n;
    int freevars = A.gaussian();
    return (1LL << freevars) - 1;
}

int main()
{
    prime_sieve();

    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%d", &n);

        A.clr();
        for (int i = 0; i < n; ++i) {
            i64 x;
            scanf("%lld", &x);
            process(x, i);
        }

        printf("%lld\n", solve());
    }

    return 0;
}

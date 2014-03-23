#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <limits>
#include <utility>
#include <vector>
using namespace std;

typedef pair<int, int> II;
typedef vector<II>     IIV;
typedef vector<int>    IV;
typedef long long      i64;
typedef unsigned int   u32;

#define Sc(t,v) static_cast<t>(v)
#define Zero(v) memset(v, 0, sizeof(v))
#define Iter(t,v)   t::iterator v
#define For(t,v,c)  for(t::iterator v=c.begin(); v != c.end(); v++)
#define cFor(t,v,c) for(t::const_iterator v=c.begin(); v != c.end(); v++)
#define crFor(t,v,c) \
    for(t::const_reverse_iterator v=c.rbegin(); v != c.rend(); v++)

// I/O
#define BUF 65536
struct Reader {
    char buf[BUF]; char b; int bi, bz;
    Reader() { bi=bz=0; read(); }
    void read() {
        if (bi==bz) { bi=0; bz = fread(buf, 1, BUF, stdin); }
        b = bz ? buf[bi++] : 0; }
    void skip() { while (b > 0 && b <= 32) read(); }
    u32 nextU32() {
        u32 v = 0; for (skip(); b > 32; read()) v = v*10 + b-48; return v; }
};

// Number Theory
#define ISCOMP(n)  (_c[(n)>>5]&(1<<((n)&31)))
#define SETCOMP(n) _c[(n)>>5]|=(1<<((n)&31))
namespace Num
{
    const int MAX = 100;   // sqrt(10000)
    const int LMT = 10;    // sqrt(MAX)
    int _c[(MAX>>5)+1];
    IV primes;
    void primeSieveList() {
        SETCOMP(0); SETCOMP(1);
        for (int i = 3; i <= LMT; i += 2)
            if (!ISCOMP(i)) for (int j = i*i; j <= MAX; j+=i+i) SETCOMP(j);
        primes.push_back(2);
        for (int i=3; i <= MAX; i+=2) if (!ISCOMP(i)) primes.push_back(i);
    }
    void primeFactorization(int n, IIV &f) {
        int sn = Sc(int, sqrt(n));
        cFor (IV, p, primes) {
            int prime = *p;
            if (prime > sn) break; if (n % prime != 0) continue;
            int e = 0; for (; n % prime == 0; e++, n /= prime);
            f.push_back(II(prime, e));
            sn = Sc(int, sqrt(n));
        }
        if (n > 1) f.push_back(II(n, 1));
    }
    int ipow(int b, int e) {
        int res = 1; for (; e; e >>= 1, b *= b) if (e & 1) res *= b;
        return res;
    }
}

// Big Integer
#define BIBAS 1000
#define BIDIG 3
#define BIFMT "%03d"
struct Bigint {
    IV d; bool sgn;
    Bigint(i64 n=0) {
        if (n < 0) sgn = true, n = -n; else sgn = false;
        if (n < BIBAS) d.push_back(n);
        else while (n != 0) { d.push_back(n % BIBAS); n /= BIBAS; }
    }
    size_t len() const { return d.size(); }
    Bigint &operator*=(const Bigint &b) {
        int s1 = len(), s2 = b.len(), s3 = s1+s2;
        IV res(s3); int c = 0;
        for (int k=0; k < s3; k++) {
            int sum = c;
            for (int i=max(0,k-s2+1), I=min(k+1, s1), j=k-i; i < I; i++, j--)
                sum += d[i] * b.d[j];
            if (sum >= BIBAS) { c = sum / BIBAS; sum %= BIBAS; } else c = 0;
            res[k] = sum;
        }
        d = res; sgn ^= b.sgn; clean();
        return *this;
    }
    void clean() {
        Iter(IV, i); for (i=d.end()-1; *i == 0 && i != d.begin(); i--);
        d.erase(i+1, d.end());
        if (sgn && d.size() == 1 && d[0] == 0) sgn = false;
    }
    void println() {
        if (sgn) putchar('-');
        bool flg = true;
        crFor (IV, i, d) {
            if (flg) { printf("%d", *i); flg=false; }
            else printf(BIFMT, *i);
        } putchar('\n');
    }
};

#define MAXNUM 10000

// fac[i] is the prime factorization of i
IIV fac[MAXNUM + 1];

// pe[i] is the max exponent of the prime number i for the LCM
int pe[MAXNUM + 1];

void prepare()
{
    Num::primeSieveList();

    for (int i = 2; i <= MAXNUM; i++)
        Num::primeFactorization(i, fac[i]);
}

int main()
{
    prepare();

    Reader rr;

    int T = rr.nextU32();

    int ncase = 1;
    while (T--) {
        int n = rr.nextU32();

        IV primesUsed;
        Zero(pe);

        while (n--) {
            int desec = rr.nextU32();
            cFor (IIV, f, fac[desec]) {
                if (pe[f->first] == 0) {
                    pe[f->first] = f->second;
                    primesUsed.push_back(f->first);
                }
                else if (f->second > pe[f->first])
                    pe[f->first] = f->second;
            }
        }

        IV factors;
        cFor (IV, p, primesUsed)
            factors.push_back(Num::ipow(*p, pe[*p]));
        sort(factors.begin(), factors.end());

        Bigint ans;
        bool ans_set(false);
        i64 tmp_ans = 1;

        cFor (IV, f, factors) {
            // Check if doing this multiplication overflows
            if (numeric_limits<i64>::max() / tmp_ans < *f) {
                if (ans_set) ans *= Bigint(tmp_ans);
                else ans = Bigint(tmp_ans), ans_set = true;

                tmp_ans = *f;
            }
            else tmp_ans *= *f;
        }


        if (ans_set) {
            ans *= Bigint(tmp_ans);
            printf("Case %d: ", ncase++);
            ans.println();
        }
        else
            printf("Case %d: %lld\n", ncase++, tmp_ans);
    }

    return 0;
}

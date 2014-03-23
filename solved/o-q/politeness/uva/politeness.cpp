#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
using namespace std;


#define MOD 1000000007LL

#define Zero(v) memset((v), 0, sizeof(v))

const int MAX_DIVS    = 7149;     // e^(1.066*log(n)/log(log(n)))
const int MAX_MEMO_ID = MAX_DIVS;
const int MAX_MEMO_IP = 41;       // log2(MAXP)


typedef long long i64;


#define IsComp(n)  (_c[n>>6]&(1<<((n>>1)&31)))
#define SetComp(n) _c[n>>6]|=(1<<((n>>1)&31))
const int MAXP   = 1000000;
const int SQRP   =    1000;  // sqrt(MAX)
const int MAX_NP =   91202;  // 1.26 * MAXP/log(MAXP)
int _c[(MAXP>>6)+1];
int    primes[MAX_NP];
double lprimes[MAX_NP];
int    nprimes;
void prime_sieve() {
    for (int i = 3; i <= SQRP; i += 2)
        if (!IsComp(i)) for (int j = i*i; j <= MAXP; j+=i+i) SetComp(j);
    primes[nprimes++] = 2;
    for (int i=3; i <= MAXP; i+=2) if (!IsComp(i)) primes[nprimes++] = i;
    for (int i = 0; i < nprimes; ++i)
        lprimes[i] = log(primes[i]);
}

template <typename T>
void divisors(T n, T *ds, int &s)
{
    s = 0;
    ds[s++] = 1;
    int sn = sqrt(n);
    for (int i = 0; i < nprimes; ++i) {
        int &p = primes[i];
        if (p > sn) break;
        if (n % p != 0) continue;
        T q = 1; int t = s;
        while (n % p == 0) {
            q *= p, n /= p;
            for (int j = 0; j < t; ++j) ds[s++] = ds[j] * q;
        }
        sn = sqrt(n);
    }
    if (n > 1) {
        int t = s;
        for (int j = 0; j < t; ++j) ds[s++] = ds[j] * n;
    }
}

template <typename TB, typename TE>
TB mod_pow(TB b, TE e, TB m) {
    TB res = 1; for (; e; e >>= 1, b = b*b%m) if (e & 1) res = res*b%m;
    return res;
}

struct PFactor {
    int p;     // prime number
    i64 e;     // exponent
    int i, j;  // indices for the next prime factor
    PFactor() {}
    PFactor(int P, i64 E, int I=-1, int J=-1) : p(P), e(E), i(I), j(J) {}
};


i64 P;
i64 D[MAX_DIVS];  // list of all relevant divisors
int nd;           // number of divisors

double  lmemo[MAX_MEMO_ID][MAX_MEMO_IP];
PFactor pmemo[MAX_MEMO_ID][MAX_MEMO_IP];
bool    vis[MAX_MEMO_ID][MAX_MEMO_IP];


template <typename T>
int binsearch(const T *a, int lo, int hi, T v)
{
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (a[mid] < v) lo = mid + 1;
        else            hi = mid - 1;
    }
    return a[lo] == v ? lo : -1;
}

/*
 * Finds the lowest number that has D[id] odd divisors. Returns
 * e1*log(p1) + e2*log(p2) + ... based on the prime factorization of the
 * result
 *
 *   id: index in the D array of the number to process
 *   ip: index of the next prime number to consider
 */
double f(int id, int ip)
{
    if (vis[id][ip]) return lmemo[id][ip];

    i64 &x = D[id];
//    printf("  f(%d, %d) x: %llu\n", id, ip, x);

    double l = (x - 1) * lprimes[ip];
    pmemo[id][ip] = PFactor(primes[ip], x - 1);

    for (int i = 1; i < id; ++i) {
        if (x % D[i] != 0) continue;

        double l1 = (D[i] - 1) * lprimes[ip];
        if (l1 > l) break;

        int    new_id = binsearch(D, 0, nd - 1, x / D[i]);
        double l2     = f(new_id, ip + 1);

        if (l1 + l2 < l) {
            l = l1 + l2;
            pmemo[id][ip] = PFactor(primes[ip], D[i]-1, new_id, ip + 1);
        }
    }

    vis[id][ip] = true;
    return lmemo[id][ip] = l;
}

int solve()
{
    i64 x = P + 1;  // number of odd divisors that the number must have
    divisors(x, D, nd);
    sort(D, D + nd);

    /*
    printf("  x: %llu  nd: %d\n", x, nd);
    for (int i = 0; i < nd; ++i) printf("   %lld\n", D[i]);
    */

    Zero(vis);
    f(nd-1, 1);

    i64 ans = 1;
    int a, b;
    for (int i = nd-1, j = 1; i >= 0; ) {
        ans = ans * mod_pow(1LL*pmemo[i][j].p, pmemo[i][j].e, MOD) % MOD;
        a = pmemo[i][j].i;
        b = pmemo[i][j].j;
        i = a, j = b;
    }

    return ans;
}

int main()
{
    prime_sieve();

    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%lld", &P);
        printf("%d\n", solve());
    }

    return 0;
}

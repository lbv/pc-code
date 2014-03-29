#include <cstdio>
#include <cstring>


#define MAXI 10000

#define MAX_PRIMES 1368

#define Clr(m) memset(m, 0, sizeof(m))


typedef long long i64;
typedef unsigned int u32;


struct Reader {
    int b; Reader() { read(); }
    void read() { b = getchar_unlocked(); }
    void skip() { while (b >= 0 && b <= 32) read(); }

    u32 next_u32() {
        u32 v = 0; for (skip(); b > 32; read()) v = 10*v+b-48; return v; }
};


int hfac[MAXI + 1];  // highest prime factor
int prod[MAXI + 1];  // product of prime factors
int primes[MAX_PRIMES];
int nprimes;
void basic_sieve()
{
	for (int i = 1; i <= MAXI; ++i) hfac[i] = prod[i] = 1;

	nprimes = 0;
	for (int i = 2; i <= MAXI; ++i)
		if (prod[i] == 1) {
			hfac[i] = prod[i] = i;
			primes[nprimes++] = i;
			for (int j = i + i; j <= MAXI; j += i)
				hfac[j] = i, prod[j] *= i;
		}
}

template <typename T>
T choose(T n, T k) {
	if (k > n) return 0;
	if (n-k < k) k = n-k;
	T r=1;
	for (T d = 1; d <= k; d++)
		r *= n--, r /= d;
	return r;
}


struct Prod {
	int p, n;  // product, number of primer factors
	Prod() {}
	Prod(int P, int N): p(P), n(N) {}
};


int N;
int mulcnt[MAXI + 1];  // count of multiples among the N numbers



// divisors formed by distinct primes (5 is the max number of prime factors)
int divs[MAXI + 1][1 << 5];
int ndiv[MAXI + 1];

Prod prods[MAXI];
int nprod;


i64 solve()
{
	i64 ans = choose<i64>(N, 4);

	for (int i = 0; i < nprod; ++i) {
		Prod &p = prods[i];
		int sgn = p.n % 2 != 0 ? -1 : 1;

		ans += choose<i64>(mulcnt[p.p], 4) * sgn;
	}

	return ans;
}

void dfs(int p, int n, int next)
{
	if (next >= nprimes) return;
	dfs(p, n, next + 1);

	int pp = p * primes[next];
	if (pp > MAXI) return;
	prods[nprod++] = Prod(pp, n + 1);

	dfs(pp, n+1, next + 1);
}

void prepare()
{
	basic_sieve();

	int factors[5];
	int nfac;
	for (int i = 1; i <= MAXI; ++i) {
		nfac = 0;
		for (int x = prod[i]; x != 1; x /= hfac[x])
			factors[nfac++] = hfac[x];

		u32 bitm = 1 << nfac;
		for (u32 j = 0; j < bitm; ++j) {
			int d = 1;

			for (int k = 0; k < nfac; ++k)
				if (j & (1 << k)) d *= factors[k];

			divs[i][ ndiv[i]++ ] = d;
		}
	}

	dfs(1, 0, 0);
}

int main()
{
	prepare();

	Reader rr;
	int T = rr.next_u32();

	int ncase = 0;
	while (T--) {
		N = rr.next_u32();

		Clr(mulcnt);
		for (int i = 0; i < N; ++i) {
			int n = rr.next_u32();

			for (int i = 0; i < ndiv[n]; ++i)
				++mulcnt[ divs[n][i] ];
		}

		printf("Case %d: %lld\n", ++ncase, solve());
	}

	return 0;
}

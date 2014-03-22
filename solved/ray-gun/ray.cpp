#include <algorithm>
#include <cstdio>
using namespace std;


#define MAXN 1000000


typedef long long i64;


#define IsComp(n)  (_c[n>>6]&(1<<((n>>1)&31)))
#define SetComp(n) _c[n>>6]|=(1<<((n>>1)&31))
const int MAXP	 = MAXN;
const int SQRP	 = 1000;
const int MAX_NP = 91202;  // 1.26 * MAXP/log(MAXP)
int _c[(MAXP>>6)+1];
int primes[MAX_NP];
int nprimes;
void prime_sieve() {
	for (int i = 3; i <= SQRP; i += 2)
		if (!IsComp(i)) for (int j = i*i; j <= MAXP; j+=i+i) SetComp(j);
	primes[nprimes++] = 2;
	for (int i=3; i <= MAXP; i+=2) if (!IsComp(i)) primes[nprimes++] = i;
}


// A possible product of prime factors, to count the number of coprimes
struct Prod {
	int v;  // value of the product
	int n;  // number of prime factors involved

	Prod(){}
	Prod(int V, int N): v(V), n(N) {}
	bool operator<(const Prod &p) const { return v < p.v; }
};

Prod prods[MAXN];
int nprods;


i64 solve(i64 m, i64 n)
{
	if (m < n) swap(m, n);
	if (m == 0) return 0;
	if (n == 0) return 1;

	i64 ans = 2 + m*n;

	for (int i = 0; i < nprods; ++i) {
		Prod &p = prods[i];
		if (p.v > n) break;

		if (p.n % 2 == 0)
			ans += (m/p.v) * (n/p.v);
		else
			ans -= (m/p.v) * (n/p.v);
	}

	return ans;
}

/*
 * Calculate all products of prime factors <= MAXN
 *   p:   current product
 *   n:   current number of factors
 *   nxt: index of next prime factor to consider
 */
void dfs(int p, int n, int nxt)
{
	for (int i = nxt; i < nprimes; ++i) {
		if (primes[i] > MAXN / p) return;

		int v = p * primes[i];
		prods[nprods++] = Prod(v, n+1);

		dfs(v, n + 1, i + 1);
	}
}

void prepare()
{
	prime_sieve();

	dfs(1, 0, 0);
	sort(prods, prods + nprods);
}

int main()
{
	prepare();

	int T;
	scanf("%d", &T);

	int m, n;
	int ncase = 0;
	while (T--) {
		scanf("%d%d", &m, &n);
		printf("Case %d: %lld\n", ++ncase, solve(m, n));
	}

	return 0;
}

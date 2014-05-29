#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;


#if 0
#define MAXT 100
#define MAXN 1000
#define MAXI 1000000000000000LL
#define NCRIT 5
#define NL	 0
#endif

#if 1
#define MAXT 20
#define MAXN 60
#define MAXI 10000000
#define NCRIT 2
#define NL	 1
#endif


typedef long long i64;


#define IsComp(n)  (_c[n>>6]&(1<<((n>>1)&31)))
#define SetComp(n) _c[n>>6]|=(1<<((n>>1)&31))
const int MAXP	 = 300;
const int SQRP	 =	18;  // sqrt(MAX)
const int MAX_NP =	67;  // 1.26 * MAXP/log(MAXP)
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


int T;
int np;  // number of primes to choose from for building the numbers


i64 gen_integer()
{
	int nf = rand() % 30 + 1;
	i64 n = 1;

	while (nf--) {
		int p = primes[rand() % np];

		if (n <= MAXI / p)
			n *= p;
	}
	return n;
}

void gen(bool crit = false)
{
#if NL
	puts("");
#endif

	int n = crit ? MAXN : rand() % MAXN + 1;
	printf("%d\n", n);

	np = rand() % nprimes + 1;
	random_shuffle(primes, primes + nprimes);

	for (int i = 0; i < n; ++i) {
		if (i > 0) putchar(' ');
		printf("%lld", gen_integer());
	}
	putchar('\n');

	--T;
}

int main()
{
	prime_sieve();
	srand(time(NULL));

	T = MAXT;
	printf("%d\n", T);

	for (int i = 0; i < NCRIT; ++i) gen(true);
	while (T) gen();

	return 0;
}

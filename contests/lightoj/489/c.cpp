/**
 * LightOJ Contest #489: BUBT Codehacker Monthly Contest May-14
 *
 * Problem C: Mr. Toothless and His Number Theory
 *
 * Keywords:
 *   - number theory
 *   - primes
 *   - palindromes
 */

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;


typedef long long i64;


#define IsComp(n)  (_c[n>>6]&(1<<((n>>1)&31)))
#define SetComp(n) _c[n>>6]|=(1<<((n>>1)&31))
const int MAXP	 = 100000;  // sqrt(10^5)
const int SQRP	 = 317;     // sqrt(MAX)
const int MAX_NP = 10945;   // 1.26 * MAXP/log(MAXP)
int _c[(MAXP>>6)+1];
int primes[MAX_NP];
int nprimes;
void prime_sieve() {
	for (int i = 3; i <= SQRP; i += 2)
		if (!IsComp(i)) for (int j = i*i; j <= MAXP; j+=i+i) SetComp(j);
	primes[nprimes++] = 2;
	for (int i=3; i <= MAXP; i+=2) if (!IsComp(i)) primes[nprimes++] = i;
}


vector<i64> pp;  // palindromic primes
char aux[16];

void process()
{
	i64 n;
	sscanf(aux, "%lld", &n);

	bool is_prime = true;
	int sn = sqrt(n);
	for (int i = 0; ; ++i) {
		int p = primes[i];
		if (p > sn) break;

		if (n % p == 0) {
			is_prime = false;
			break;
		}
	}

	if (is_prime)
	pp.push_back(n);
}

void dfs(int ndig, bool inner, char *x)
{
	if (inner) {
		for (int i = 0; i <= 9; ++i) {
			x[0] = x[ndig-1] = '0' + i;
			if (ndig == 1)
				process();
			else
				dfs(ndig - 2, true, x + 1);
		}
	}
	else {
		x[ndig] = 0;
		for (int i = 1; i <= 9; ++i) {
			x[0] = x[ndig-1] = '0' + i;
			dfs(ndig - 2, true, x + 1);
		}
	}
}


i64 A, B;


void prepare()
{
	prime_sieve();
	pp.push_back(2);
	pp.push_back(3);
	pp.push_back(5);
	pp.push_back(7);
	pp.push_back(11);

	for (int d = 3; d <= 9; d += 2)
		dfs(d, false, aux);
}


int solve()
{
	return upper_bound(pp.begin(), pp.end(), B) -
		lower_bound(pp.begin(), pp.end(), A);
}

int main()
{
	prepare();

	int T;
	scanf("%d", &T);

	while (T--) {
		scanf("%lld%lld", &A, &B);
		printf("%d\n", solve());
	}

	return 0;
}

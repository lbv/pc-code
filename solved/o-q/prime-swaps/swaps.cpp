#include <cstdio>


#define MAXN 100000


// Prime sieve
#define IsComp(n)  (_c[n>>6]&(1<<((n>>1)&31)))
#define SetComp(n) _c[n>>6]|=(1<<((n>>1)&31))
const int MAXP	 = 100000; // MAXN
const int SQRP	 = 317;    // sqrt(MAX)
const int MAX_NP = 10945;  // 1.26 * MAXP/log(MAXP)
int _c[(MAXP>>6)+1];
int primes[MAX_NP];
int nprimes;
void prime_sieve() {
	for (int i = 3; i <= SQRP; i += 2)
		if (!IsComp(i)) for (int j = i*i; j <= MAXP; j+=i+i) SetComp(j);
	primes[nprimes++] = 2;
	for (int i=3; i <= MAXP; i+=2) if (!IsComp(i)) primes[nprimes++] = i;
}
bool is_prime(int n) {
	if (n < 2 || n % 2 == 0) return n == 2;
	return ! IsComp(n);
}


int n, k;
int a[MAXN + 1];
int pos[MAXN + 1];

int sol[MAXN*5][2];

int prime_sum[MAXN+1];


void prepare()
{
	prime_sieve();

	for (int i = 4; i <= MAXN; i += 2)
		for (int j = 0; j < nprimes; ++j) {
			int p = primes[j];

			if (is_prime(p) && is_prime(i - p)) {
				prime_sum[i] = p;
				break;
			}
		}
}

void swp(int i, int j)
{
	int x = a[i];
	int y = a[j];

	pos[x] = j;
	pos[y] = i;
	a[i] = y;
	a[j] = x;

	sol[k][0] = i;
	sol[k][1] = j;
	++k;
}

void solve()
{
	for (int i = 1; i <= n; ++i) {
		int j = pos[i];
		if (j == i) continue;

		int d = j - i + 1;
		if (is_prime(d)) {
			swp(i, j);
			continue;
		}

		if (d % 2 != 0) {
			swp(j-1, j);
			--j;
			--d;
		}

		int ps = prime_sum[d];
		swp(j - ps + 1, j);
		swp(i + 1, j - ps + 1);
		swp(i, i + 1);
	}
}

int main()
{
	prepare();

	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		pos[ a[i] ] = i;
	}

	solve();
	printf("%d\n", k);
	for (int i = 0; i < k; ++i)
		printf("%d %d\n", sol[i][0], sol[i][1]);

	return 0;
}

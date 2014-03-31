#include <algorithm>
#include <cstdio>
using namespace std;


#define MAXB 10000000000LL
#define SQRB 100000

// Estimation of perfect powers <= MAXB
#define MAXPP 103000

#define MOD 100000007

const int MAXFACT = 2*MAXPP;


typedef long long i64;


template<typename T>
void ext_euclid(T a, T b, T &x, T &y, T &g) {
	x = 0; y = 1; g = b;
	T m, n, q, r;
	for (T u=1, v=0; a != 0; g=a, a=r) {
		q = g / a; r = g % a;
		m = x-u*q; n = y-v*q;
		x=u; y=v; u=m; v=n;
	}
}

template<typename T>
T mod_inv(T n, T m) {
	T x, y, gcd;
	ext_euclid(n, m, x, y, gcd);
	if (gcd != 1) return 0;
	if (x < 0) x += m;
	else if (x >= m) x %= m;
	return x;
}

int fact[MAXFACT];

template<typename T>
T catalan_mod(T n)
{
	T f1 = fact[2*n];
	T f2 = mod_inv<T>(fact[n], MOD);
	T f3 = mod_inv<T>(n+1, MOD);

	T ans = f1*f2;
	if (ans >= MOD) ans %= MOD;
	ans *= f2;
	if (ans >= MOD) ans %= MOD;
	ans *= f3;
	if (ans >= MOD) ans %= MOD;
	return ans;
}


i64 a, b;

i64 pp[MAXPP]; // perfect powers
int npp;


int count_powers()
{
	return upper_bound(pp, pp + npp, b) - upper_bound(pp, pp + npp, a - 1);
}

int solve()
{
	int cnt = count_powers();
	if (cnt == 0) return 0;
	return catalan_mod<i64>(cnt);
}

bool vis[SQRB + 1];
void prepare()
{
	for (int i = 2; i <= SQRB; ++i) {
		if (vis[i]) continue;

		for (i64 n = 1LL*i*i; n <= MAXB; n *= i) {
			pp[npp++] = n;
			if (n <= SQRB)
				vis[n] = true;
		}
	}
	sort(pp, pp + npp);

	fact[0] = 1;
	for (int i = 1; i <= MAXFACT; ++i) {
		i64 f = 1LL * fact[i-1] * i;
		if (f >= MOD) f %= MOD;
		fact[i] = f;
	}
}

int main()
{
	prepare();

	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%lld%lld", &a, &b);
		printf("Case %d: %d\n", ++ncase, solve());
	}

	return 0;
}

#include <cstdio>


#define MOD 33554431


template <typename TB, typename TE>
TB mod_pow(TB b, TE e, TB m) {
	TB res = 1; for (; e; e >>= 1, b = b*b%m) if (e & 1) res = res*b%m;
	return res;
}

int N;

int solve()
{
	int ans = 1 + mod_pow<long long, int>(2, N + 1, MOD) - 2 + MOD;
	ans %= MOD;
	return ans;
}


int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d", &N);
		printf("Case %d: %d\n", ++ncase, solve());
	}

	return 0;
}

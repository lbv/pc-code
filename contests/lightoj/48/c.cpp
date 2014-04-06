/**
 * LightOJ Contest #48: IIUPC - 2011
 *
 * Problem C: All in Wall-E
 *
 * Keywords:
 *   - discrete math
 */

#include <cmath>
#include <cstdio>


typedef long long i64;


int G, N, K;


template<typename TB, typename TE>
TB sq_pow(TB b, TE e) {
	TB res = 1; for (; e; e >>= 1, b *= b) if (e & 1) res *= b;
	return res;
}

i64 sum(int n)
{
	return (sq_pow<i64, int>(K, n + 1) - 1) / (K-1);
}

i64 solve()
{
	if (K == 1) return G;

	int g = log(N) / log(K);

	if (g == G) return sum(G - 1);
	return sum(g) + 1LL * N * (G - 1 - g);
}

int main()
{
	int T;
	scanf("%d", &T);

	while (T--) {
		scanf("%d%d%d", &G, &N, &K);
		printf("%lld\n", solve());
	}

	return 0;
}

/**
 * LightOJ Contest #505: MBSTU CodeBeat S03E02
 *
 * Problem C: Cows and Goats
 *
 * Keywords:
 *   - diophantine equations
 *   - extended euclid
 */

#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;


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


int A, B, K;


i64 solve()
{
	i64 X, Y, G;
	ext_euclid(1LL * A, 1LL * B, X, Y, G);

	if (K % G != 0) return 0;

	X *= K/G;
	Y *= K/G;

	i64 hi = floor(1.0 * X * G / B);
	i64 lo = ceil(1.0 * -Y * G / A);

	return max(0LL, hi - lo + 1);
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d%d%d", &A, &B, &K);
		printf("Case %d: %lld\n", ++ncase, solve());
	}

	return 0;
}

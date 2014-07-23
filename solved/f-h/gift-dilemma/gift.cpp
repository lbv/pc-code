#include <cstdio>


typedef long long i64;


template<typename T>
void ext_euclid(T a, T b, T &x, T &y, T &g) {
	x = 0, y = 1, g = b;
	T m, n, q, r;
	for (T u=1, v=0; a != 0; g=a, a=r) {
		q = g / a, r = g % a;
		m = x-u*q, n = y-v*q;
		x=u, y=v, u=m, v=n;
	}
}

//
// ceil(x/y) and floor(x/y) for positive y
//
template<typename T>
T int_ceil(T x, T y) { return x > 0 ? (x-1)/y + 1 : x/y; }
template<typename T>
T int_floor(T x, T y) { return x >= 0 ? x/y : (x+1)/y - 1; }



i64 A, B, C, P;


i64 solve()
{
	i64 x, y, g;
	ext_euclid(A, B, x, y, g);

	i64 ans = 0;

	for (i64 z = P; z >= 0; z -= C) {
		if (z % g != 0) continue;

		i64 hi = int_floor(x*z, B);
		i64 lo = int_ceil(-y*z, A);

		ans += hi >= lo ? hi - lo + 1 : 0;
	}

	return ans;
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%lld%lld%lld%lld", &A, &B, &C, &P);
		printf("Case %d: %lld\n", ++ncase, solve());
	}

	return 0;
}

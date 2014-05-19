#include <cstdio>


typedef long long i64;


i64 W, N, M;


bool solve()
{
	if (W & 1) return false;

	i64 half = W/2;
    i64 div, mod, den;
    int p = 1;

    den = 1 << p;
    while (true) {
        div = W / den;
        mod = W % den;
        if (mod != 0) continue;

        if ((div & 1) == 1) {
            N = div;
            M = den;
            return true;
        }

		den <<= 1;
        if (den > half) return false;
    }
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%lld", &W);
		printf("Case %d: ", ++ncase);

		if (solve())
			printf("%lld %lld\n", N, M);
		else
			puts("Impossible");
	}

	return 0;
}

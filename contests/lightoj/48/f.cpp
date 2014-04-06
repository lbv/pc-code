/**
 * LightOJ Contest #48: IIUPC - 2011
 *
 * Problem F: Find the Sum
 *
 * Keywords:
 *   - math
 */

#include <cstdio>


#define MOD 10007


typedef long long i64;


int n;


int main()
{
	int T;
	scanf("%d", &T);

	while (T--) {
		i64 s = 0;
		scanf("%d", &n);
		while (n--) {
			int a;
			scanf("%d", &a);

			s = (s + a + (s*a%MOD)) % MOD;
		}

		printf("%lld\n", s);
	}

	return 0;
}

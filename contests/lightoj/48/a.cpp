/**
 * LightOJ Contest #48: IIUPC - 2011
 *
 * Problem A: Coat on Hot Day
 *
 * Keywords:
 *   - math
 *   - beginner
 */

#include <cstdio>


int C;


double solve()
{
	return 9.0 * C / 5.0 + 32.0;
}

int main()
{
	int T;
	scanf("%d", &T);

	while (T--) {
		scanf("%d", &C);
		printf("%.2lf\n", solve());
	}

	return 0;
}

/**
 * LightOJ Contest #489: BUBT Codehacker Monthly Contest May-14
 *
 * Problem D: Mr. Toothless and His Easy Problem
 *
 * Keywords:
 *   - beginner
 *   - math
 */

#include <cstdio>


int N;


int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d", &N);
		int dig = 1;

		for (int i = 0; i < N; ++i) {
			int x;
			scanf("%d", &x);
			dig = dig * x % 10;
		}

		printf("Case %d: %d\n", ++ncase, dig);
	}

	return 0;
}

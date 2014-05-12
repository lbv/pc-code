/**
 * LightOJ Contest #489: BUBT Codehacker Monthly Contest May-14
 *
 * Problem F: Mr. Toothless and His Equation
 *
 * Keywords:
 *   - bitwise calculations
 */

#include <cstdio>


typedef unsigned long long u64;


u64 A, B;


int solve()
{
	int ans = 0;

	for (; A || B; A >>= 1, B >>= 1)
		if ((A & 1) != (B & 1))
			++ans;

	return ans;
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%llu%llu", &A, &B);
		printf("Case %d: %d\n", ++ncase, solve());
	}

	return 0;
}

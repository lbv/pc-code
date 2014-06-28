/**
 * LightOJ Contest #505: MBSTU CodeBeat S03E02
 *
 * Problem B: RhyHan and The King - Easy
 *
 * Keywords:
 *   - beginner
 */

#include <algorithm>
#include <cstdio>
using namespace std;


typedef unsigned int u32;


u32 A, B, C;
u32 hi, total;


void solve()
{
	hi = max(A, max(B, C));
	total = A + B + C;
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%u%u%u", &A, &B, &C);
		solve();
		printf("Case %d: %u %u\n", ++ncase, hi, total);
	}

	return 0;
}

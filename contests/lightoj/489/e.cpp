/**
 * LightOJ Contest #489: BUBT Codehacker Monthly Contest May-14
 *
 * Problem E: Mr. Toothless and Farmer Jon
 *
 * Keywords:
 *   - diophantine equations
 */

#include <algorithm>
#include <cstdio>
using namespace std;


int A, B, N;



int solve()
{
	if (A < B) swap(A, B);

	for (int a = N/A; a >= 0; --a)
		if ((N - a*A) % B == 0)
			return a + (N - a*A) / B;

	return -1;
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d%d%d", &A, &B, &N);
		printf("Case %d: ", ++ncase);

		int ans = solve();
		if (ans < 0)
			puts("Not Possible");
		else
			printf("%d\n", ans);
	}

	return 0;
}

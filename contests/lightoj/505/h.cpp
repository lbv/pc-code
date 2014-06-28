/**
 * LightOJ Contest #505: MBSTU CodeBeat S03E02
 *
 * Problem H: I Love One
 *
 * Keywords:
 *   - dynamic programming
 */

#include <algorithm>
#include <cstdio>
using namespace std;


#define MAXN 10000000


int dp[MAXN + 1];
int N;


void prepare()
{
	for (int i = 2; i <= MAXN; ++i) {
		dp[i] = dp[i-1] + 1;

		if (i % 2 == 0) dp[i] = min(dp[i], dp[i/2] + 1);
		if (i % 3 == 0) dp[i] = min(dp[i], dp[i/3] + 1);
	}
}

int main()
{
	prepare();

	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d", &N);
		printf("Case %d: %d\n", ++ncase, dp[N]);
	}

	return 0;
}

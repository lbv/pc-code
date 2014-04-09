#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;


#define MAXN 100
#define MAXM 100
#define MAXANS 50000

#define Neg(m) memset(m, -1, sizeof(m))


int n, m;
int times[MAXN][2];

// dp[i][j] (Implicit parameter t): maximum number of jobs from the second
// project that can be completed by employees [0..i] having assigned j jobs
// to the first project
int dp[MAXN][MAXM + 1];


bool check(int t)
{
	Neg(dp);

	for (int j = min(m, t / times[0][0]); j >= 0; --j)
		dp[0][j] = (t - j*times[0][0]) / times[0][1];

	for (int i = 1; i < n; ++i) {
		int jobs1 = min(m, t / times[i][0]);

		for (int j = 0; j <= m && dp[i-1][j] >= 0; ++j)
			dp[i][j] = dp[i-1][j];

		for (int j = jobs1; j >= 0; --j) {
			int jobs2 = (t - j*times[i][0]) / times[i][1];

			for (int k = j; k <= m; ++k) {
				if (dp[i-1][k - j] < 0) break;
				dp[i][k] = max(dp[i][k], dp[i-1][k-j] + jobs2);
			}
		}
	}

	return dp[n-1][m] >= m;
}

int solve()
{
	int lo = 1, hi = MAXANS;

	while (lo <= hi) {
		int mid = (hi + lo) / 2;

		if (check(mid)) hi = mid - 1;
		else lo = mid + 1;
	}

	return lo;
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d%d", &n, &m);
		for (int i = 0; i < n; ++i)
			scanf("%d%d", &times[i][0], &times[i][1]);

		printf("Case %d: %d\n", ++ncase, solve());
	}

	return 0;
}

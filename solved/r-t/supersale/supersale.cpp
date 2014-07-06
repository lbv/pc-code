#include <algorithm>
#include <cstdio>
using namespace std;


#define MAXN 1000
#define MAXW 30
#define MAXG 100


int N, G;
int ps[MAXN];  // prices
int ws[MAXN];  // weights
int gs[MAXG];  // peoples capacities

// dp[i][j]: maximum value that can be picked by one person from the first i
// products, having j capacity left
int dp[MAXN + 1][MAXW + 1];


int solve()
{
	int maxg = *max_element(gs, gs + G);
	for (int i = 0; i <= N; ++i)
		for (int j = 0; j <= maxg; ++j) {
			int &best = dp[i][j];

			if (i == 0) { best = 0; continue; }
			best = dp[i-1][j];

			int w = j - ws[i-1];
			if (w >= 0)
				best = max(best, dp[i-1][w] + ps[i-1]);
		}

	int ans = 0;
	for (int i = 0; i < G; ++i)
		ans += dp[N][ gs[i] ];

	return ans;
}

int main()
{
	int T;
	scanf("%d", &T);

	while (T--) {
		scanf("%d", &N);
		for (int i = 0; i < N; ++i) scanf("%d%d", &ps[i], &ws[i]);

		scanf("%d", &G);
		for (int i = 0; i < G; ++i) scanf("%d", &gs[i]);

		printf("%d\n", solve());
	}

	return 0;
}

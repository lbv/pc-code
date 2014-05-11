#include <algorithm>
#include <cstdio>
using namespace std;


#define MAXN 1000
#define MAXM 1000



int n, m;
int sw[MAXN][MAXN];
int se[MAXN][MAXN];
int nw[MAXN][MAXN];
int ne[MAXN][MAXN];
int grid[MAXN][MAXM];


int solve()
{
	for (int i = n - 1; i >= 0; --i)
		for (int j = 0; j < m; ++j) {
			int &dp = sw[i][j];

			dp = 0;
			if (i < n - 1) dp = max(dp, sw[i+1][j]);
			if (j > 0)     dp = max(dp, sw[i][j-1]);

			dp += grid[i][j];
		}

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j) {
			int &dp = nw[i][j];

			dp = 0;
			if (i > 0) dp = max(dp, nw[i-1][j]);
			if (j > 0) dp = max(dp, nw[i][j-1]);

			dp += grid[i][j];
		}

	for (int i = n - 1; i >= 0; --i)
		for (int j = m - 1; j >= 0; --j) {
			int &dp = se[i][j];

			dp = 0;
			if (i < n - 1) dp = max(dp, se[i+1][j]);
			if (j < m - 1) dp = max(dp, se[i][j+1]);

			dp += grid[i][j];
		}

	for (int i = 0; i < n; ++i)
		for (int j = m - 1; j >= 0; --j) {
			int &dp = ne[i][j];

			dp = 0;
			if (i > 0)     dp = max(dp, ne[i-1][j]);
			if (j < m - 1) dp = max(dp, ne[i][j+1]);

			dp += grid[i][j];
		}

	int ans = 0;

	for (int i = 1, I = n-1; i < I; ++i)
		for (int j = 1, J = m-1; j < J; ++j) {
			ans = max(ans, nw[i-1][j] + se[i+1][j] + sw[i][j-1] + ne[i][j+1]);
			ans = max(ans, nw[i][j-1] + se[i][j+1] + sw[i+1][j] + ne[i-1][j]);
		}
	return ans;
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			scanf("%d", &grid[i][j]);

	printf("%d\n", solve());

	return 0;
}

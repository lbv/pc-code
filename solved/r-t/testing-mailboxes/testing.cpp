#include <algorithm>
#include <cstdio>
using namespace std;


#define MAXM 100
#define MAXK 100

#define INF 0x3f3f3f3f


int k, m;

// dp[i][j][k]: the minimum number of firecrackers to use, given that a
// mailbox has capacity in the range [i:j] and we have k mailboxes left.
int dp[MAXM + 1][MAXM + 1][MAXK + 1];


int sum(int x) { return x*(x+1)/2; }

void prepare()
{
	for (int i = 1; i <= MAXM; ++i)
		for (int j = i; j <= MAXM; ++j)
			dp[i][j][1] = sum(j) - sum(i-1);

	for (int k = 2; k <= MAXK; ++k)
		for (int i = MAXM; i >= 1; --i)
			for (int j = i; j <= MAXM; ++j) {
				int &best = dp[i][j][k];

				best = INF;
				for (int p = i; p <= j; ++p) {
					int above = p < j ? p + dp[p+1][j][k] : p;
					int below = p > i ? p + dp[i][p-1][k-1] : p;

					best = min(best, max(above, below));
				}
			}
}

int main()
{
	prepare();

	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d%d", &k, &m);
		printf("Case %d: %d\n", ++ncase, dp[1][m][k]);
	}

	return 0;
}

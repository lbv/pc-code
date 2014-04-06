/**
 * LightOJ Contest #48: IIUPC - 2011
 *
 * Problem I: Guttu
 *
 * Keywords:
 *   - dynamic programming
 */

#include <cstdio>


#define MAXN 200
#define MAXK 20
#define MOD  12345


// dp[i][j]: Number of ways to fill the i'th box, putting j marbles in it
int dp[MAXK + 1][MAXN + 1];

// prefix sum of dp[][]
int psum[MAXK+1][MAXN+1];

int N, K;


int first_digit(int n)
{
	for (; n / 10 > 0; n /= 10) ;
	return n;
}

void prepare()
{
	for (int j = 1; j <= MAXN; ++j)
		dp[1][j] = 1;

	for (int i = 2; i <= MAXK; ++i)
		for (int j = 1; j <= MAXN; ++j) {
			int d = first_digit(j);

			for (int k = 1; k < j; ++k)
				if (k % 10 != d) {
					dp[i][j] += dp[i-1][k];

					if (dp[i][j] >= MOD) dp[i][j] %= MOD;
				}
		}

	for (int i = 1; i <= MAXK; ++i)
		for (int j = 1; j <= MAXN; ++j) {
			psum[i][j] = psum[i][j-1] + dp[i][j];

			if (psum[i][j] >= MOD) psum[i][j] %= MOD;
		}
}

int main()
{
	prepare();

	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d%d", &N, &K);
		printf("Case %d: %d\n", ++ncase, psum[K][N]);
	}

	return 0;
}

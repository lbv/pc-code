#include <cstdio>


#define MAXN 100
#define MOD 1000000007


int n, k, d;
int dp[MAXN+1];


int calc(int K)
{
	dp[0] = 1;
	for (int i = 1; i <= n; ++i) {
		dp[i] = 0;
		for (int j = 1; j <= K; ++j) {
			int pre = i - j;
			if (pre < 0) continue;

			dp[i] += dp[pre];
			if (dp[i] >= MOD) dp[i] %= MOD;
		}
	}

	return dp[n];
}

int solve()
{
	int ans = calc(k);

	if (d > 1) ans -= calc(d-1);

	if (ans < 0) ans += MOD;
	return ans;
}

int main()
{
	scanf("%d%d%d", &n, &k, &d);
	printf("%d\n", solve());

	return 0;
}

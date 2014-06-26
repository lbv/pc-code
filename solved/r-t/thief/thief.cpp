#include <algorithm>
#include <cstdio>
using namespace std;


#define MAXN 100
#define MAXW 10000


struct Item {
	int p, w;

	bool operator<(const Item &x) const { return w < x.w; }
};


Item items[MAXN];
int n, W;

// dp[i]: maximum profit for i weight
int dp[MAXW + 1];


int solve()
{
	sort(items, items + n);

	dp[0] = 0;
	for (int w = 1; w <= W; ++w) {
		dp[w] = 0;
		for (int i = 0; i < n && items[i].w <= w; ++i)
			dp[w] = max(dp[w], dp[w - items[i].w] + items[i].p);
	}

	return dp[W];
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d%d", &n, &W);
		for (int i = 0; i < n; ++i) {
			int p, c, w;
			scanf("%d%d%d", &p, &c, &w);

			items[i].p = p;
			items[i].w = w;
			W -= c * w;
		}
		printf("Case %d: ", ++ncase);

		if (W < 0) puts("Impossible");
		else printf("%d\n", solve());
	}

	return 0;
}

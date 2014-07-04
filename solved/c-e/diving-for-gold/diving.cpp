#include <cstdio>


#define MAXT 1000
#define MAXN 30


struct State {
	int n;  // number of treasures

	int pt, pn;  // indices for the previous state in the trail
};

int t, w, n;
int ds[MAXN];  // depths
int gs[MAXN];  // gold values

int dp[MAXT + 1][MAXN + 1];
State ss[MAXT + 1][MAXN + 1];

bool vis[MAXT + 1][MAXN + 1];
int cvis;


int f(int t, int n)
{
	if (vis[t][n] == cvis) return dp[t][n];
	vis[t][n] = cvis;

	int &ans = dp[t][n];

	if (n == 0) {
		ss[t][n] = (State) { 0, -1, -1 };
		return ans = 0;
	}

	ans = f(t, n-1);
	ss[t][n] = ss[t][n-1];

	int t2 = t - ds[n-1]*w*3;
	if (t2 >= 0) {
		int dp2 = f(t2, n-1) + gs[n-1];
		if (dp2 > ans) {
			ans = dp2;

			ss[t][n] = (State) { ss[t2][n-1].n + 1, t2, n-1 };
		}
	}

	return ans;
}

void print_treasures(int t, int n)
{
	State &s = ss[t][n];
	if (s.pt < 0) return;
	print_treasures(s.pt, s.pn);
	printf("%d %d\n", ds[s.pn], gs[s.pn]);
}

void solve()
{
	++cvis;
	int gold = f(t, n);

	printf("%d\n%d\n", gold, ss[t][n].n);
	print_treasures(t, n);
}

int main()
{
	bool first = true;
	while (scanf("%d%d%d", &t, &w, &n) == 3) {
		for (int i = 0; i < n; ++i)
			scanf("%d%d", &ds[i], &gs[i]);

		if (first)
			first = false;
		else
			putchar('\n');

		solve();
	}

	return 0;
}

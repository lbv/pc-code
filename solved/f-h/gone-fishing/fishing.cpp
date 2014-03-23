#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;


#define MAXN 25

const int MAXT = 16 * 60 / 5 + 1;

#define Memset(m,v) memset(m, v, sizeof(m))
#define Clr(m) Memset(m,0)


struct State {
	int f;  // total amount of fish
	int c;  // amount of fish taken from the current lake
	int t;  // time spent in the current lake
	bool v; // is the state valid?

	State() {}
	State(int F, int C, int T): f(F), c(C), t(T), v(true) {}

	bool operator<(const State &s) const {
		if (v != s.v) return !v;
		return f < s.f;
	}
};


int n, h;
int fs[MAXN];
int ds[MAXN];
int ts[MAXN];

// dp[i][j]: Best solution in lake i, after j periods of time have passed
State dp[MAXN][MAXT];


void print_lake_times(int i, int j)
{
	if (i > 0) {
		print_lake_times(i - 1, j - dp[i][j].t - ts[i-1]);
		printf(", ");
	}

	printf("%d", dp[i][j].t * 5);
}

void solve()
{
	Clr(dp);

	dp[0][0] = State(0, 0, 0);

	int t = h * 60 / 5;

	for (int i = 0; i < n; ++i)
		for (int j = 0; j <= t; ++j) {
			State &cur = dp[i][j];

			if (j > 0) {
				State &s1 = dp[i][j-1];
				if (s1.v) {
					int f = max(0, fs[i] - s1.t * ds[i]);
					cur = State(s1.f + f, s1.c + f, s1.t + 1);
				}

				if (cur.v && i > 0) {
					int f = dp[i-1][j - s1.t - ts[i-1]].f + s1.c;
					if (f >= cur.f)
						cur = State(f, s1.c, s1.t);
				}
			}

			if (i > 0 && j - ts[i-1] >= 0) {
				State &s2 = dp[i-1][j - ts[i-1]];
				if (s2.v && !(s2 < cur))
					cur = State(s2.f, 0, 0);
			}
		}

	int lake = -1, fish = 0;

	for (int i = 0; i < n; ++i)
		if (dp[i][t].v && dp[i][t].f > fish)
			lake = i, fish = dp[i][t].f;

	print_lake_times(lake, t);
	for (int i = lake + 1; i < n; ++i) printf(", 0");

	printf("\nNumber of fish expected: %d\n", fish);
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d%d", &n, &h);
		for (int i = 0; i < n; ++i) scanf("%d", &fs[i]);
		for (int i = 0; i < n; ++i) scanf("%d", &ds[i]);
		for (int i = 0, I = n - 1; i < I; ++i) scanf("%d", &ts[i]);

		printf("Case %d:\n", ++ncase);
		solve();
	}

	return 0;
}

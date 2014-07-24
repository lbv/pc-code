#include <cstdio>
#include <cstring>


#define MAXN 12

#define Clr(m) memset(m, 0, sizeof(m))

#define PosLSB(x) (__builtin_ctzll(x))
#define GetLSB(x) ((x) & -(x))
#define ClrLSB(x) (x &= ~GetLSB(x))


typedef unsigned int u32;


// Returns first integer with exactly n bits set
u32 popcnt_init(int n) { return (1 << n) - 1; }

// next higher number with same number of 1's in binary
u32 popcnt_next(u32 n)
{
	u32 c = (n & -n), r = n+c;
	return (((r ^ n) >> 2) / c) | r;
}


int n, k, q;

bool enemies[MAXN][MAXN];

// dp[b][i][j]: number of permutations using the people in bitmask b, after
// placing i last, with exactly j conflicts.
int dp[1 << MAXN][MAXN][MAXN];

int totals[MAXN];

void run_dp()
{
	Clr(dp);

	for (int i = 0; i < n; ++i)
		dp[1 << i][i][0] = 1;

	u32 all = (1 << n) - 1;
	for (int nbits = 2; nbits <= n; ++nbits) {
		for (u32 b = popcnt_init(nbits); b <= all; b = popcnt_next(b)) {
			for (u32 x = b; x; ClrLSB(x)) {
				int ix = PosLSB(x);

				u32 rest = b & ~GetLSB(x);
				for (u32 y = rest; y; ClrLSB(y)) {
					int iy = PosLSB(y);

					if (enemies[iy][ix])
						for (int c = 1; c < nbits; ++c)
							dp[b][ix][c] += dp[rest][iy][c-1];
					else
						for (int c = 0; c < nbits; ++c)
							dp[b][ix][c] += dp[rest][iy][c];
				}
			}
		}
	}

	Clr(totals);
	for (int i = 0; i < n; ++i)
		for (int c = 0; c < n; ++c)
			totals[c] += dp[all][i][c];

	for (int i = 1; i < n; ++i)
		totals[i] += totals[i-1];
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d%d%d", &n, &k, &q);

		Clr(enemies);
		for (int i = 0; i < n; ++i) {
			int t;
			scanf("%d", &t);
			for (int j = 0; j < t; ++j) {
				int v;
				scanf("%d", &v);
				enemies[i][v-1] = true;
			}
		}

		run_dp();

		printf("Case %d:\n", ++ncase);
		while (q--) {
			int r;
			scanf("%d", &r);

			int conflicts = (k == 0 || r/k >= n) ? n-1 : r/k;

			printf("%d\n", totals[conflicts]);
		}
	}

	return 0;
}

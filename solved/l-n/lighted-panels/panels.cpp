#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;


#define MAXR 8
#define MAXC 8

#define INF (MAXR * MAXC + 10)

#define Zero(v) memset((v), 0, sizeof(v))

typedef unsigned int u32;


char grid[MAXR][MAXC + 1];
u32 panels[MAXR];
u32 row_mask;
int R, C;

int memo[MAXR][1 << MAXC][1 << MAXC];
bool vis[MAXR][1 << MAXC][1 << MAXC];

// three consecutive lights in a row
const u32 mask3 = 7;


// next higher number with same number of 1's in binary
u32 next_popcount(u32 n)
{
    u32 c = (n & -n);
    u32 r = n+c;
    return (((r ^ n) >> 2) / c) | r;
}
// Returns first integer with exactly n bits set
u32 init_popcount(int n) { return (1 << n) - 1; }


void init_panels()
{
	Zero(panels);
	for (int i = 0; i < R; ++i)
		for (int j = 0; j < C; ++j)
			if (grid[i][j] == '*')
				panels[i] |= 1 << j;
}

void toggle_lights(int row, u32 mask)
{
	u32 group_mask = 0;

	for (int j = 0; j < C; ++j) {
		if (! (mask & (1 << j))) continue;

		group_mask ^= j >= 1 ? mask3 << (j - 1) : mask3 >> 1;
	}

	group_mask &= row_mask;

	panels[row] ^= group_mask;
	if (row > 0) panels[row-1] ^= group_mask;
	if (row + 1 < R) panels[row+1] ^= group_mask;
}

#define NEXT_ROW (row + 1 < R ? panels[row+1] : 0)

// dp(i, a, b): minimum number of presses required to turn on all lights,
// from row i to R-1, where a and b are bitmasks of the current state of
// rows (i-1) and (i), respectively
int dp(int row, u32 prev, u32 curr)
{
	if (row == R)
		return panels[R-1] == row_mask ? 0 : INF;

	if (vis[row][prev][curr]) return memo[row][prev][curr];

	int res = INF;

	if (row == 0 || panels[row-1] == row_mask)
		res = min(res, dp(row + 1, panels[row], NEXT_ROW));

	for (int n = 1; n <= C; ++n)
		for (u32 b = init_popcount(n); b <= row_mask; b = next_popcount(b)) {
			toggle_lights(row, b);

			if (row == 0 || panels[row-1] == row_mask)
				res = min(res, dp(row + 1, panels[row], NEXT_ROW) + n);

			toggle_lights(row, b);
		}

	vis[row][prev][curr] = true;
	return memo[row][prev][curr] = res;
}

int solve()
{
	init_panels();
	Zero(vis);
	row_mask = (1 << C) - 1;
	return dp(0, 0, panels[0]);
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d%d", &R, &C);
		for (int i = 0; i < R; ++i) scanf("%s", grid[i]);

		printf("Case %d: ", ++ncase);

		int ans = solve();
		if (ans == INF)
			puts("impossible");
		else
			printf("%d\n", ans);
	}

	return 0;
}

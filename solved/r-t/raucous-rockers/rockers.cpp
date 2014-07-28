#include <algorithm>
#include <cstdio>
using namespace std;


#define MAXN 1024
#define MAXM 128
#define MAXT 128


typedef short i16;


// dp[a][b][c]: maximum number of songs that can be recorded, using the
// first a songs, and the first b disks, having c minutes left in the last
// disc.
i16 dp[MAXN+1][MAXM+1][MAXT+1];

i16 vis[MAXN+1][MAXM+1][MAXT+1];
i16 cvis;

int n, t, m;
int songs[MAXN];


i16 f(int a, int b, int c)
{
	if (vis[a][b][c] == cvis) return dp[a][b][c];
	vis[a][b][c] = cvis;
	i16 &best = dp[a][b][c];

	// no more songs or discs
	if (a == 0 || b == 0) return best = 0;

	int cur = songs[a-1];

	// don't use this last song
	best = f(a-1, b, c);

	// use the last song, but not the last disc, because it doesn't fit
	if (cur <= t && cur > c)
		best = max(best, f(a, b-1, t));

	// if it fits, use the last song and last disc
	if (cur <= c) {
		i16 fp = 1 + f(a-1, b, c-cur);
		best = max(best, fp);
	}

	return best;
}

int solve()
{
	++cvis;
	return f(n, m, t);
}

int main()
{
	int T;
	scanf("%d", &T);

	bool first = true;
	while (T--) {
		scanf("%d%d%d", &n, &t, &m);
		for (int i = 0; i < n; ++i) scanf("%d ,", &songs[i]);

		if (first) first = false;
		else putchar('\n');

		printf("%d\n", solve());
	}

	return 0;
}

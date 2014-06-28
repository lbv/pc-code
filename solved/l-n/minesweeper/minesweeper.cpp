#include <cstdio>


#define MAXN 100
#define MAXM 100


char grid[MAXN][MAXM + 1];
int n, m;

const int moves[8][2] = {
	{ -1, -1 },
	{ -1,  0 },
	{ -1,  1 },
	{  0, -1 },
	{  0,  1 },
	{  1, -1 },
	{  1,  0 },
	{  1,  1 }
};
const int nmoves = 8;


bool valid_pos(int r, int c)
{
	return 0 <= r && r < n && 0 <= c && c < m && grid[r][c] != '*';
}

void solve()
{
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			if (grid[i][j] == '.') grid[i][j] = '0';

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			if (grid[i][j] == '*')
				for (int k = 0; k < nmoves; ++k)
					if (valid_pos(i + moves[k][0], j + moves[k][1]))
						++grid[ i + moves[k][0] ][ j + moves[k][1] ];
}

int main()
{
	int ncase = 0;
	while (true) {
		scanf("%d%d", &n, &m);
		if (n == 0 && m == 0) break;
		for (int i = 0; i < n; ++i) scanf("%s", grid[i]);

		solve();

		if (ncase > 0) putchar('\n');
		printf("Field #%d:\n", ++ncase);
		for (int i = 0; i < n; ++i) puts(grid[i]);
	}

	return 0;
}

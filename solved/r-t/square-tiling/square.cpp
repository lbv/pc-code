#include <cstdio>
#include <cstring>


#define MAXN 100
#define MAXM 100


#define Clr(m) memset(m, 0, sizeof(m))


int n, m;
char grid[MAXN][MAXM + 1];
bool vis[MAXN][MAXM];

bool paints[8];



void check_cell(int r, int c)
{
	if (r < 0 || r >= n || c < 0 || c >= m || grid[r][c] == 0) return;
	paints[ grid[r][c] - 'A' ] = true;
}

char choose_paint(int r, int c)
{
	Clr(paints);
	check_cell(r-1, c);
	check_cell(r, c+1);
	check_cell(r, c-1);

	for (int i = 0; i < 8; ++i)
		if (! paints[i])
			return 'A' + i;
	return '?';
}

void fill(int r, int c)
{
	int h = n - r;
	int w;

	char p = choose_paint(r, c);

	for (w = 1; w < h && c + w < m; ++w)
		if (vis[r][c + w] || choose_paint(r, c + w) != p) break;

	for (int i = 0; i < w; ++i)
		for (int j = 0; j < w; ++j) {
			grid[r + i][c + j] = p;
			vis[r + i][c + j] = true;
		}
}

void solve()
{
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			if (! vis[i][j])
				fill(i, j);
}

int main()
{
	scanf("%d%d", &n, &m);
	solve();
	for (int i = 0; i < n; ++i) puts(grid[i]);

	return 0;
}

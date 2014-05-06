#include <cstdio>


#define MAXN 300


int n;
char grid[MAXN][MAXN + 1];


bool solve()
{
	char x = grid[0][0];
	char y = grid[0][1];

	if (x == y) return false;

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			if (i == j || i == (n-1) - j) {
				if (grid[i][j] != x) return false;
			}
			else {
				if (grid[i][j] != y) return false;
			}

	return true;
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) scanf("%s", grid[i]);

	if (solve()) puts("YES");
	else puts("NO");

	return 0;
}

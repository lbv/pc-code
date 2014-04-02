#include <algorithm>
#include <cstdio>
using namespace std;


#define MAXR 100
#define MAXC 100


struct Grid {
	char g[MAXR][MAXC + 1];
};

const int adj[4][2] = {
	{ -1,  0 },
	{  1,  0 },
	{  0,  1 },
	{  0, -1 }
};


int r, c, n;

Grid g1, g2;
Grid *grid, *aux;


bool is_valid(int i, int j)
{
	return 0 <= i && i < r && 0 <= j && j < c;
}

bool beats(int i, int j, int p, int q)
{
	char a = grid->g[i][j];
	char b = grid->g[p][q];

	return (a == 'R' && b == 'S') ||
		(a == 'S' && b == 'P') ||
		(a == 'P' && b == 'R');
}

// simulates a single time step, return true if there were any changes.
bool time_step()
{
	int changes = 0;

	for (int i = 0; i < r; ++i)
		for (int j = 0; j < c; ++j) {
			aux->g[i][j] = grid->g[i][j];

			for (int k = 0; k < 4; ++k) {
				int p = i + adj[k][0];
				int q = j + adj[k][1];

				if (is_valid(p, q) && beats(p, q, i, j)) {
					++changes;
					aux->g[i][j] = grid->g[p][q];
					break;
				}
			}
		}

	swap(grid, aux);

	return changes > 0;
}

void solve()
{
	for (int i = 0; i < n; ++i)
		if (! time_step()) break;

	for (int i = 0; i < r; ++i) {
		for (int j = 0; j < c; ++j)
			putchar(grid->g[i][j]);
		putchar('\n');
	}
}

int main()
{
	int t;
	scanf("%d", &t);

	for (int _t = 0; _t < t; ++_t) {
		if (_t > 0) putchar('\n');

		grid = &g1, aux = &g2;
		scanf("%d%d%d", &r, &c, &n);
		for (int i = 0; i < r; ++i) scanf("%s", grid->g[i]);

		solve();
	}

	return 0;
}

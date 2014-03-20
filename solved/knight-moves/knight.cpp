#include <cstdio>


#define INF 1000


const int moves[8][2] = {
	{ -2, -1 },
	{ -2,  1 },
	{ -1, -2 },
	{ -1,  2 },
	{  1, -2 },
	{  1,  2 },
	{  2, -1 },
	{  2,  1 }
};

#define Pos(i,j) ((i) * 8 + (j))


int g[64][64];
char c1, r1, c2, r2;


int idx(char c, char r)
{
	int i = c - 'a';
	int j = r - '1';
	return Pos(i, j);
}

int solve()
{
	int u = idx(c1, r1);
	int v = idx(c2, r2);

	return g[u][v];
}

bool valid_pos(int i, int j)
{
	return 0 <= i && i < 8 && 0 <= j && j < 8;
}

void floyd_warshall()
{
	for (int k = 0; k < 64; k++)
		for(int i = 0; i < 64; i++)
			for (int j = 0; j < 64; j++) {
				if (g[i][k] == INF || g[k][j] == INF) continue;
				int t = g[i][k] + g[k][j];
				if (t < g[i][j]) g[i][j] = t;
			}
}

void prepare()
{
	for (int i = 0; i < 64; ++i)
		for (int j = 0; j < 64; ++j)
			g[i][j] = INF;

	for (int i = 0; i < 8; ++i)
		for (int j = 0; j < 8; ++j) {
			g[Pos(i, j)][Pos(i, j)] = 0;

			for (int k = 0; k < 8; ++k) {
				int ti = i + moves[k][0];
				int tj = j + moves[k][1];
				if (! valid_pos(ti, tj)) continue;

				g[Pos(i, j)][Pos(ti, tj)] = 1;
			}

		}

	floyd_warshall();
}

int main()
{
	prepare();
	while (true) {
		if (scanf(" %c%c %c%c", &c1, &r1, &c2, &r2) != 4) break;

		printf("To get from %c%c to %c%c takes %d knight moves.\n",
		       c1, r1, c2, r2, solve());
	}

	return 0;
}

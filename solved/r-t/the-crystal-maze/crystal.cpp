#include <cstdio>
#include <cstring>


#define MAXM 500
#define MAXN 500

#define Neg(m) memset(m, -1, sizeof(m))


struct Pos {
	int r, c;
};

char grid[MAXM][MAXN + 1];
int M, N, Q;

int group_map[MAXM][MAXN];
int groups[MAXM * MAXN];
int ngroups;

Pos q[MAXM * MAXN];
int qfront, qback;

const int deltas[4][2] = {
	{ -1,  0 },
	{  1,  0 },
	{  0,  1 },
	{  0, -1 }
};


void visit(int r, int c, int g)
{
	q[qback++] = (Pos) { r, c };
	group_map[r][c] = g;
}

bool visitable(int r, int c)
{
	return 0 <= r && r < M && 0 <= c && c < N && group_map[r][c] < 0 &&
		grid[r][c] != '#';
}

void solve(int r, int c)
{
	qfront = 0, qback = 0;

	int current = ngroups++;
	groups[current] = 0;

	visit(r, c, current);

	while (qfront < qback) {
		Pos pos = q[qfront++];

		if (grid[pos.r][pos.c] == 'C')
			++groups[current];

		for (int i = 0; i < 4; ++i) {
			int r2 = pos.r + deltas[i][0];
			int c2 = pos.c + deltas[i][1];

			if (visitable(r2, c2))
				visit(r2, c2, current);
		}
	}
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d%d%d", &M, &N, &Q);
		for (int i = 0; i < M; ++i) scanf("%s", grid[i]);
		printf("Case %d:\n", ++ncase);

		Neg(group_map);
		ngroups = 0;

		while (Q--) {
			int x, y;
			scanf("%d%d", &x, &y);
			--x, --y;

			if (group_map[x][y] < 0) solve(x, y);
			printf("%d\n", groups[ group_map[x][y] ]);
		}
	}

	return 0;
}

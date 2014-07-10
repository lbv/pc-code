#include <cstdio>
#include <cstring>


#define MAXR 12
#define MAXC 12

#define UP (1 << 0)
#define RT (1 << 1)
#define DN (1 << 2)
#define LT (1 << 3)
#define END (1 << 4)


typedef unsigned int u32;


int R, C;
int grid[MAXR+2][MAXC+2];
char desc[5];

u32 grid_rot[MAXR+2][MAXC+2];

const u32 rotations[5][5] = {
	{ 0, END, 0, 0, 0 },
	{ UP, RT, DN, LT, END },
	{ UP|RT, RT|DN, DN|LT, LT|UP, END },
	{ UP|RT|DN, RT|DN|LT, DN|LT|UP, LT|UP|RT, END },
	{ UP|RT|DN|LT, END, 0, 0, 0 }
};


bool check_horizontal(u32 lt, u32 rt)
{
	bool a = lt & RT;
	bool b = rt & LT;

	return a == b;
}

bool check_vertical(u32 up, u32 dn)
{
	bool a = up & DN;
	bool b = dn & UP;

	return a == b;
}

bool dfs(int r, int c)
{
	if (r == R+2) return true;

	int lines = grid[r][c];
	u32 &cur = grid_rot[r][c];

	for (int i = 0; rotations[lines][i] != END; ++i) {
		cur = rotations[lines][i];

		if (! check_horizontal(grid_rot[r][c-1], cur) ||
			! check_vertical(grid_rot[r-1][c], cur))
			continue;

		int r2 = r, c2 = c + 1;
		if (c2 == C+2) ++r2, c2 = 1;

		if (dfs(r2, c2)) return true;
	}

	return false;
}

bool solve()
{
	return dfs(1, 1);
}

int main()
{
	while (true) {
		scanf("%d%d", &R, &C);
		if (R == 0) break;

		for (int i = 1; i <= R; ++i) {
			for (int j = 1; j <= C; ++j) {
				scanf("%s", desc);
				grid[i][j] = desc[0] == 'x' ? 0 : strlen(desc);
			}
			grid[i][C+1] = 0;
		}
		for (int j = 1; j <= C+1; ++j) grid[R+1][j] = 0;

		puts(solve() ? "SOLVABLE" : "UNSOLVABLE");
	}

	return 0;
}

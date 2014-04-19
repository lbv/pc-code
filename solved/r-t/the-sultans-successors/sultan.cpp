#include <cstdio>


const int MAX_BOARDS = 128;  // an overestimation


typedef unsigned int u32;


struct Pos {
    int r, c;
    Pos() {}
    Pos(int R, int C) : r(R), c(C) {}
};

struct Board {
    Pos q[8];
};


int grid[8][8];

Board boards[MAX_BOARDS];
int   nboards;


void find_boards(Board &board, int n, u32 col, u32 diag1, u32 diag2)
{
    if (n == 8) {
        boards[nboards++] = board;
        return;
    }

    for (int i = 0; i < 8; ++i) {
        int d1 = 7 - (n - i);
        int d2 = n + i;
        if (col & (1 << i) ||
            diag1 & (1 << d1) ||
            diag2 & (1 << d2))
            continue;
        board.q[n] = Pos(n, i);
        find_boards(board, n + 1, col | (1 << i),
                    diag1 | (1 << d1), diag2 | (1 << d2));
    }
}

void prepare()
{
    Board board;
    find_boards(board, 0, 0, 0, 0);
}

int solve()
{
	int best = 0;
	for (int i = 0; i < nboards; ++i) {
		int cur = 0;

		for (int j = 0; j < 8; ++j) {
			Pos &p = boards[i].q[j];
			cur += grid[p.r][p.c];
		}

		if (cur > best) best = cur;
	}

	return best;
}

int main()
{
	prepare();

	int k;
	scanf("%d", &k);

	while (k--) {
		for (int i = 0; i < 8; ++i)
			for (int j = 0; j < 8; ++j)
				scanf("%d", &grid[i][j]);
		printf("%5d\n", solve());
	}

	return 0;
}

#include <cstdio>
#include <cstring>


#define MAXNUM 75

#define Clr(m) memset(m, 0, sizeof(m))
#define Neg(m) memset(m, -1, sizeof(m))


int board[5][5];
int turn;
bool bingo;

int loc[MAXNUM + 1][2];

// count of marked numbers in each row/col/diagonal
int crow[5];
int ccol[5];
int cdia[2];


void read_board()
{
	Neg(loc);
	Clr(crow);
	Clr(ccol);
	Clr(cdia);

	for (int i = 0; i < 5; ++i)
		for (int j = 0; j < 5; ++j) {
			if (i == 2 && j == 2) continue;

			int num;
			scanf("%d", &num);

			loc[num][0] = i;
			loc[num][1] = j;
			board[i][j] = num;
		}

	// the centre position is "free"
	++crow[2]; ++ccol[2]; ++cdia[0]; ++cdia[1];

	bingo = false;
}

void check_number(int n)
{
	int r = loc[n][0], c = loc[n][1];
	if (r < 0) return;

	++crow[r]; ++ccol[c];
	if (r == c) ++cdia[0];
	if (c == 5 - r - 1) ++cdia[1];

	if (crow[r] == 5 || ccol[c] == 5 || cdia[0] == 5 || cdia[1] == 5) {
		bingo = true;
		printf("BINGO after %d numbers announced\n", turn);
	}
}

int main()
{
	int n;
	scanf("%d", &n);

	while (n--) {
		read_board();

		int number;
		for (turn = 1; turn <= 75; ++turn) {
			if (bingo)
				scanf("%*d");
			else {
				scanf("%d", &number);
				check_number(number);
			}
		}
	}

	return 0;
}

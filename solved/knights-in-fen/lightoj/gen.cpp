#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
using namespace std;


#define MAXT 100
#define MAX_MOVES 15


int T;
char board[5][6];
char aux[25];

const int moves[8][2] = {
	{ -2, -1 },
	{ -1, -2 },
	{  1, -2 },
	{  2, -1 },
	{  2,  1 },
	{  1,  2 },
	{ -1,  2 },
	{ -2,  1 }
};


void print_board()
{
	for (int i = 0; i < 5; ++i)
		printf("%s\n", board[i]);
}

bool valid_pos(int r, int c)
{
	return 0 <= r && r < 5 && 0 <= c && c < 5;
}

void test_case_random()
{
	aux[0] = ' ';
	int p = 1;
	for (int i = 0; i < 12; ++i) aux[p++] = '1';
	for (int i = 0; i < 12; ++i) aux[p++] = '0';

	random_shuffle(aux, aux + 25);

	p = 0;
	for (int i = 0; i < 5; ++i)
		for (int j = 0; j < 5; ++j)
			board[i][j] = aux[p++];

	print_board();
	--T;
}

void test_case_good()
{
	strcpy(board[0], "11111");
	strcpy(board[1], "01111");
	strcpy(board[2], "00 11");
	strcpy(board[3], "00001");
	strcpy(board[4], "00000");

	int r = 2, c = 2;

	int nmoves = rand() % (MAX_MOVES + 1);

	while (nmoves--) {
		int nr, nc;
		do {
			int m = rand() % 8;
			nr = r + moves[m][0];
			nc = c + moves[m][1];
		} while (! valid_pos(nr, nc));

		swap(board[r][c], board[nr][nc]);
	}

	print_board();
	--T;
}

int main()
{
	srand(time(NULL));

	T = MAXT;
	printf("%d\n", T);

	while (T) {
		int r = rand() % 10;
		if (r < 7) test_case_good();
		else test_case_random();
	}

	return 0;
}

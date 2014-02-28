#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>


#define MAXR 8
#define MAXC 8
#define MAXT 125

#define Zero(v) memset((v), 0, sizeof(v))

typedef unsigned int u32;


int R, C;
u32 panels[MAXR];
u32 row_mask;


void toggle(int r, int c)
{
	u32 b = c >= 1 ? 7 << (c - 1) : 7 >> 1;
	b &= row_mask;

	panels[r] ^= b;
	if (r > 0) panels[r-1] ^= b;
	if (r + 1 < R) panels[r+1] ^= b;
}

void init_grid()
{
	R = rand() % MAXR + 1;
	C = rand() % MAXC + 1;

	Zero(panels);

	row_mask = (1 << C) - 1;
}

void print_case()
{
	printf("%d %d\n", R, C);
	for (int i = 0; i < R; ++i) {
		for (int j = 0; j < C; ++j) {
			printf("%c", panels[i] & (1 << j) ? '*' : '.');
		}
		puts("");
	}
}

void test_case1()
{
	init_grid();

	int n = rand() % (R * C);

	while (n--) {
		int i = rand() % R;
		int j = rand() % C;

		toggle(i, j);
	}

	print_case();
}

void test_case2()
{
	init_grid();

	int n = rand() % (R * C);

	while (n--) {
		int i = rand() % R;
		int j = rand() % C;

		panels[i] ^= 1 << j;
	}

	print_case();
}

int main()
{
	srand(time(NULL));

	int T = MAXT;
	printf("%d\n", T);

	printf(
"3 3\n"
"***\n"
"*.*\n"
"***\n"); --T;

	printf(
"2 4\n"
"****\n"
"****\n"); --T;

	printf(
"4 2\n"
"**\n"
"**\n"
"**\n"
"**\n"); --T;

	while (T--) {
		int r = rand() % 10;
		if (r < 8) test_case1();
		else test_case2();
	}

	return 0;
}

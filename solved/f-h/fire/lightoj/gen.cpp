#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 50
#define MAXR 200
#define MAXC 200
#define NCRIT 3
#endif

#if 1
#define MAXT 20
#define MAXR 8
#define MAXC 8
#define NCRIT 3
#endif


int T;
char grid[MAXR][MAXC + 1];


void gen(bool crit = false)
{
	int R = crit ? MAXR : rand() % MAXR + 1;
	int C = crit ? MAXC : rand() % MAXC + 1;
	printf("%d %d\n", R, C);

	for (int i = 0; i < R; ++i)
		for (int j = 0; j < C; ++j)
			grid[i][j] = '.';

	int obs = rand() % 60;
	for (int i = 0; i < R; ++i)
		for (int j = 0; j < C; ++j)
			if (rand() % 100 < obs)
				grid[i][j] = '#';

	int fir = rand() % 30;
	for (int i = 0; i < R; ++i)
		for (int j = 0; j < C; ++j)
			if (rand() % 100 < fir)
				grid[i][j] = 'F';

	int jr = rand() % R;
	int jc = rand() % C;
	grid[jr][jc] = 'J';

	for (int i = 0; i < R; ++i) {
		grid[i][C] = 0;
		puts(grid[i]);
	}

	--T;
}

int main()
{
	srand(time(NULL));

	T = MAXT;
	printf("%d\n", T);

	for (int i = 0; i < NCRIT; ++i) gen(true);
	while (T) gen();

	return 0;
}

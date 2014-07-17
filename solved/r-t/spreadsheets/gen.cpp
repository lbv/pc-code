#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;


#if 0
#define MAXT 100000
#define MAXC 1000000
#endif

#if 1
#define MAXT 100
#define MAXC 1000
#endif


int T;
char col[16];


int get_coord()
{
	int c = rand() % MAXC + 1;

	if (c > 100 && rand() % 20 == 0) c = rand() % 100 + 1;
	if (c > 1000 && rand() % 15 == 0) c = rand() % 1000 + 1;
	if (c > 10000 && rand() % 10 == 0) c = rand() % 10000 + 1;

	return c;
}

void col_to_letters(int C)
{
	int len = 0;

	while (C != 0) {
		int v = C % 26;
		C /= 26;

		char d;
		if (v == 0) {
			d = 'Z';
			--C;
		}
		else
			d = 'A' - 1 + v;

		col[len++] = d;
	}
	col[len] = 0;
	for (int i = 0, j = len - 1; i < j; ++i, --j)
		swap(col[i], col[j]);
}
void gen()
{
	int R = get_coord();
	int C = get_coord();

	if (rand() % 2 == 0)
		printf("R%dC%d\n", R, C);
	else {
		col_to_letters(C);
		printf("%s%d\n", col, R);
	}
	--T;
}

int main()
{
	srand(time(NULL));

	T = MAXT;
	printf("%d\n", T);

	while (T) gen();

	return 0;
}

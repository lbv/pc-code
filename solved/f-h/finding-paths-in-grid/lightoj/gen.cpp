#include <cstdio>
#include <cstdlib>
#include <ctime>


#define MAXT 100


int T;
int row[7];


void test_case()
{
	int N = rand() % 1000000000 + 1;

	printf("%d\n", N);
	for (int i = 0; i < 7; ++i) row[i] = 0;

	for (int i = 1; i <= 4; ++i) {
		int col;
		do {
			col = rand() % 7;
		} while (row[col] != 0);
		row[col] = i;
	}

	for (int i = 0; i < 7; ++i) {
		if (i > 0) putchar(' ');
		printf("%d", row[i]);
	}
	puts("");

	--T;
}

int main()
{
	srand(time(NULL));

	T = MAXT;
	printf("%d\n", T);

	while (T) test_case();

	return 0;
}

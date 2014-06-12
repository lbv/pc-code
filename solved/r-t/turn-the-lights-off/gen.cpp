#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 1
#define MAXT 50
#define MAXR 10
#define MAXC 10
#endif


int T;
int cnt;


void gen(bool crit = false)
{
	printf("case%02d\n", cnt++);

	int p = rand() % 100 + 1;
	
	for (int i = 0; i < MAXR; ++i) {
		for (int j = 0; j < MAXC; ++j)
			putchar(rand() % 100 < p ? 'O' : '#');
		putchar('\n');
	}

	--T;
}

int main()
{
	srand(time(NULL));

	T = MAXT;

	while (T) gen();
	puts("end");

	return 0;
}

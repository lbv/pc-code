#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 20
#define MAXG 30
#define MAXN 10
#define NCRIT 3
#endif

#if 1
#define MAXT 10
#define MAXG 16
#define MAXN 10
#define NCRIT 2
#endif


int T;


void gen_rand()
{
	int g = rand() % MAXG + 1;

	while (g--) {
		int x = rand() % MAXN + 1;
		printf("%d\n", x);
		if (rand() % 2 == 0)
			puts("too high");
		else
			puts("too low");
	}

	int n = rand() % MAXN + 1;
	printf("%d\nright on\n", n);
	--T;
}

void gen(bool crit = false)
{
	int n = rand() % MAXN + 1;
	int g = crit ? MAXG : rand() % MAXG + 1;

	for (int i = 1; i < g; ++i) {
		int x;
		do {
			x = rand() % MAXN + 1;
		} while (x == n);

		printf("%d\n", x);
		if (x > n)
			puts("too high");
		else
			puts("too low");
	}
	printf("%d\nright on\n", n);

	--T;
}

int main()
{
	srand(time(NULL));

	T = MAXT;

	for (int i = 0; i < NCRIT; ++i) gen(true);
	while (T) {
		if (rand() % 3 == 0) gen_rand();
		else gen();
	}
	puts("0");

	return 0;
}

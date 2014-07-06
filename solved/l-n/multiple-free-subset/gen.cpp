#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 200
#define MAXN 100
#define MAXI 1000000000
#define NCRIT 5
#endif

#if 1
#define MAXT 20
#define MAXN 20
#define MAXI 300
#define NCRIT 3
#endif


int T;


void gen(bool crit = false)
{
	int n = crit ? MAXN : rand() % MAXN + 1;

	int maxi = rand() % MAXI + 1;
	if (maxi > 1000 && rand() % 5 == 0) maxi = 1000;
	if (maxi > 100000 && rand() % 5 == 0) maxi = 100000;
	if (maxi > 10000000 && rand() % 5 == 0) maxi = 10000000;

	printf("%d\n", n);
	for (int i = 0; i < n; ++i) {
		if (i > 0) putchar(' ');
		int x = rand() % maxi + 1;
		printf("%d", x);
	}
	putchar('\n');

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

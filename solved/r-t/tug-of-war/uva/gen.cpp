#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 1
#define MAXT 100
#define MAXN 100
#define MAXW 450
#define NCRIT 5
#endif

#if 0
#define MAXT 20
#define MAXN 10
#define MAXW 100
#define NCRIT 3
#endif


int T;


void gen(bool crit = false)
{
	int n = crit ? MAXN : rand() % (MAXN - 1) + 2;
	printf("\n%d\n", n);

	while (n--) {
		int w = rand() % MAXW + 1;
		printf("%d\n", w);
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

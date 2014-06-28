#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 200
#define MAXS 100
#define MINC 10
#define MAXC 90
#define NCRIT 10
#endif

#if 1
#define MAXT 20
#define MAXS 25
#define MINC 30
#define MAXC 70
#define NCRIT 4
#endif


const int RangeC = MAXC - MINC + 1;


int T;


void gen(bool crit = false)
{
	int s = crit ? MAXS : rand() % (MAXS - 1) + 2;

	for (int i = 0; i < s; ++i) {
		int c = rand() % RangeC + MINC;
		printf("%d ", c);
	}
	puts("0");
	--T;
}

int main()
{
	srand(time(NULL));

	T = MAXT;

	for (int i = 0; i < NCRIT; ++i) gen(true);
	while (T) gen();
	puts("0 0 0");

	return 0;
}

#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 1
#define MAXT  13
#define MAXN  100000
#define MAXX  1000000000
#define MINX  -1000000000
#define MAXX2 10000
#define MINX2 -10000
#endif

#if 0
#define MAXT  20
#define MAXN  20
#define MAXX  1000
#define MINX  -1000
#define MAXX2 100
#define MINX2 -100
#define NL	  1
#endif


const int RangeX  = MAXX - MINX + 1;
const int RangeX2 = MAXX2 - MINX2 + 1;

int T;


void test_case(bool crit = false)
{
#if NL
	puts("");
#endif

	int n = crit ? MAXN : rand() % MAXN + 1;
	printf("%d\n", n);

	while (n--) {
		int x = rand() % RangeX + MINX;
		int y = rand() % RangeX + MINX;

		if (rand() % 4 == 0)
			x = rand() % RangeX2 + MINX2;
		if (rand() % 4 == 0)
			y = rand() % RangeX2 + MINX2;

		printf("%d %d\n", x, y);
	}

	--T;
}

void test_crit()
{
	int n = MAXN;
	printf("%d\n", n);

	int x = rand() % RangeX + MINX;
	int y = rand() % RangeX + MINX;

	while (n--) {
		printf("%d %d\n", x, y);
	}

	 --T;
}

int main()
{
	srand(time(NULL));

	T = MAXT;
	printf("%d\n", T);

	test_crit();
	test_case(true);
	while (T) test_case();

	return 0;
}

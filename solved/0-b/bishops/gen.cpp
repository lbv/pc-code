#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 10000
#define MAXI 1000000000
#define BASE_CASES 1
#endif

#if 1
#define MAXT 100
#define MAXI 50
#define BASE_CASES 0
#endif


int T;


void test_case()
{
	int r1 = rand() % MAXI + 1;
	int c1 = rand() % MAXI + 1;
	int r2 = rand() % MAXI + 1;
	int c2 = rand() % MAXI + 1;
	printf("%d %d %d %d\n", r1, c1, r2, c2);

	--T;
}

int main()
{
	srand(time(NULL));

	T = MAXT;
	printf("%d\n", T);

#if BASE_CASES
	for (int a = 0; a < 3; ++a)
		for (int b = 0; b < 3; ++b)
			for (int c = 0; c < 3; ++c)
				for (int d = 0; d < 3; ++d) {
					printf("%d %d %d %d\n", a+1, b+1, c+1, d+1);
					printf("%d %d %d %d\n", MAXI-a, MAXI-b, MAXI-c, MAXI-d);
					printf("%d %d %d %d\n", MAXI-a, b+1, c+1, MAXI-d);
					T -= 3;
				}
#endif

	while (T) test_case();

	return 0;
}

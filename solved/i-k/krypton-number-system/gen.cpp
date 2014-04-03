#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 200
#define MAXB 6
#define MAXS 1000000000
#endif

#if 1
#define MAXT 20
#define MAXB 6
#define MAXS 1000000000
#endif


int T;


void test_case()
{
	int b = rand() % (MAXB - 1) + 2;
	int s = rand() % MAXS + 1;

	int r = rand() % 100;
	if (r < 10)
		s = rand() % 100 + 1;
	else if (r < 20)
		s = rand() % 10000 + 1;
	else if (r < 40)
		s = rand() % 1000000 + 1;

	printf("%d %d\n", b, s);
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

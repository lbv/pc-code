#include <cstdio>
#include <cstdlib>
#include <ctime>


#define MAXT 200
#define MAXN 2000000000
#define BOUND 0


int T;


void test_case()
{
	int n;
	
	int r = rand() % 10;
	if (r < 2)
		n = rand() % 1000 + 1;
	else if (r < 4)
		n = rand() % 1000000 + 1;
	else
		n = rand() % MAXN + 1;

	printf("%d\n", n);
	--T;
}

int main()
{
	srand(time(NULL));

	T = MAXT;

#if BOUND
	for (int i = 0; i < 20; ++i) {
		printf("%d\n%d\n", i + 1, MAXN - i);
		T -= 2;
	}
#endif

	while (T) test_case();

	return 0;
}

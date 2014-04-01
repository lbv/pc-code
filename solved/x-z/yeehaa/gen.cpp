#include <cstdio>
#include <cstdlib>
#include <ctime>


#define MAXT 125
#define MAXR 99900
#define MAXN 100


int T;


void test_case()
{
	int R = rand() % MAXR + 1;
	int n = rand() % (MAXN - 1) + 2;

	printf("%.2lf %d\n", 1.0 * R / 100.0, n);
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

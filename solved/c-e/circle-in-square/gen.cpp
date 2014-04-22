#include <cstdio>
#include <cstdlib>
#include <ctime>


#define MAXT 1000
#define MAXR 1000
#define MAXD 4
#define FMT "%.4lf"


int T;


void test_case()
{
	int den = 1;
	for (int i = 0; i < MAXD; ++i) den *= 10;

	int r = rand() % (MAXR * den) + 1;
	printf(FMT "\n", 1.0 * r / den);
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

#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 250000
#define MAXI 1000000
#endif

#if 1
#define MAXT 80000
#define MAXI 100000
#endif


int T;


void gen()
{
	int i = rand() % MAXI + 1;
	
	if (rand() % 10 == 0) i = rand() % 100 + 1;

	printf("%d\n", i);
	--T;
}

int main()
{
	srand(time(NULL));

	T = MAXT;

	while (T) gen();
	puts("0");

	return 0;
}

#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 10000
#define MAXN 1000000000
#define MAXM 10000
#endif

#if 1
#define MAXT 20
#define MAXN 10000
#define MAXM 100
#endif


int T;


void gen()
{
	int n, m;

	do {
		m = rand() % MAXM + 1;
		int maxmul = MAXN / (2*m);
		int mul = rand() % maxmul + 1;
		n = 2*m * mul;
	} while (n > MAXN);

	printf("%d %d\n", n, m);
	--T;
}

int main()
{
	srand(time(NULL));

	T = MAXT;
	printf("%d\n", T);

	while (T) gen();

	return 0;
}

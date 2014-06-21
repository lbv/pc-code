#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 1000
#define MAXN 1000
#endif

#if 1
#define MAXT 20
#define MAXN 1000
#endif


int T;


void gen()
{
	int N = rand() % MAXN + 1;
	int M = rand() % N + 1;
	int K = rand() % M + 1;
	printf("%d %d %d\n", N, M, K);
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

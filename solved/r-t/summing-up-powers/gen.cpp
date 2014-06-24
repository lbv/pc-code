#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 1
#define MAXT 200
#define MAXN 1000000000000000LL
#define MAXK 50
#endif

#if 0
#define MAXT 30
#define MAXN 1000000000000000LL
#define MAXK 50
#endif

typedef unsigned long long u64;


int T;
const u64 grp[] = { 100, 10000, 1000000, 1000000000 };
int ngrp = sizeof(grp) / sizeof(u64);


u64 rand_u64()
{
	u64 r = rand();
	return (r << 32) | rand();
}

void gen()
{
	u64 N = rand_u64() % MAXN + 1;
	int K = rand() % (MAXK + 1);

	int r = rand() % (ngrp + 1);
	for (int i = 0; i < ngrp; ++i)
		if (r == i && N > grp[i])
			N = rand_u64() % grp[i] + 1;

	printf("%llu %d\n", N, K);
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

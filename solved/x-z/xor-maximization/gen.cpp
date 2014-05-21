#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 1
#define MAXN 100000
#define MOD  1000000000000000000ULL
#define CRIT 1
#endif

#if 0
#define MAXN 8
#define MOD  1000000000000000ULL
#define CRIT 0
#endif


typedef unsigned long long u64;


u64 rand_u64()
{
	u64 r = rand();
	r <<= 32;
	return r | rand();
}

void gen()
{
	int N = CRIT ? MAXN : rand() % MAXN + 1;
	printf("%d\n", N);
	while (N--) {
		u64 n = rand_u64() % MOD + 1;

#if CRIT
		int r = rand() % 10;
		if (r < 2)
			n = rand() % 1000000 + 1;
		else if (r < 4)
			n = rand() % 1000 + 1;
		else if (r < 6)
			n = rand_u64() % 1000000000000ULL + 1;
#endif

		printf("%llu\n", n);
	}
}

int main()
{
	srand(time(NULL));

	gen();

	return 0;
}

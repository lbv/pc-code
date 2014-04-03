#include <cstdio>


#define MAXN 1000000
#define MOD 33554431


typedef long long i64;


int sums[MAXN + 1];


void prepare()
{
	sums[0] = 1;
	i64 x = 1;
	for (int i = 1; i <= MAXN; ++i) {
		x *= 2;
		x %= MOD;
		sums[i] = (sums[i-1] + x) % MOD;
	}
}

int main()
{
	prepare();

	int T;
	scanf("%d", &T);

	int ncase = 0;
	int N;
	while (T--) {
		scanf("%d", &N);
		printf("Case %d: %d\n", ++ncase, sums[N]);
	}

	return 0;
}

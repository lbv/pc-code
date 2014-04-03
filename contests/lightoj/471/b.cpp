#include <cstdio>


typedef long long i64;


int N, M, X;


int main()
{
	int T;
	scanf("%d", &T);

	while (T--) {
		scanf("%d%d%d", &N, &M, &X);
		i64 total = 1LL * N * M;
		if (X >= total)
			puts("No need to withdraw");
		else
			printf("Withdraw %lld taka\n", total - X);
	}

	return 0;
}

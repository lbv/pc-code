#include <cstdio>


#define MAXN 15


int N;
int ws[1 << MAXN];
int pot[1 << MAXN];


int solve()
{
	for (int i = 0, I = 1 << N; i < I; ++i) {
		pot[i] = 0;
		for (int j = 0; j < N; ++j)
			pot[i] += ws[i ^ (1 << j)];
	}

	int best = 0;
	for (int i = 0, I = 1 << N; i < I; ++i)
		for (int j = 0; j < N; ++j)
			if (pot[i] + pot[i ^ (1 << j)] > best)
				best = pot[i] + pot[i ^ (1 << j)];
	return best;
}

int main()
{
	while (scanf("%d", &N) == 1) {
		for (int i = 0, I = 1 << N; i < I; ++i)
			scanf("%d", &ws[i]);

		printf("%d\n", solve());
	}

	return 0;
}

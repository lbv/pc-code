#include <cstdio>


int K, N, M, X, Y;


void solve()
{
	if (X == N || Y == M) {
		puts("divisa");
		return;
	}

	if (Y > M) putchar('N');
	else putchar('S');

	if (X > N) puts("E");
	else puts("O");
}

int main()
{
	while (true) {
		scanf("%d", &K);
		if (K == 0) break;

		scanf("%d%d", &N, &M);
		while (K--) {
			scanf("%d%d", &X, &Y);
			solve();
		}
	}

	return 0;
}

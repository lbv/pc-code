/**
 * Slowish solution
 **/

#include <cstdio>
#include <cstring>


#define MAXN 127


int N, n;
char s1[MAXN][MAXN + 1];
char s2[MAXN][MAXN + 1];
char aux[MAXN][MAXN + 1];


void rotate()
{
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			aux[j][n - i - 1] = s2[i][j];

	memcpy(s2, aux, sizeof(s2));
}

bool is_match(int r, int c)
{
	for (int i = 0; i < n; ++i)
		if (strncmp(s1[r + i] + c, s2[i], n) != 0) return false;
	return true;
}

int count()
{
	int cnt = 0;
	for (int i = 0, I = N - n + 1; i < I; ++i)
		for (int j = 0, J = N - n + 1; j < J; ++j)
			if (is_match(i, j)) ++cnt;
	return cnt;
}

void solve()
{
	printf("%d", count());
	rotate();
	printf(" %d", count());
	rotate();
	printf(" %d", count());
	rotate();
	printf(" %d\n", count());
}

int main()
{
	while (true) {
		scanf("%d%d", &N, &n);
		if (N == 0) break;

		for (int i = 0; i < N; ++i) scanf("%s", s1[i]);
		for (int i = 0; i < n; ++i) scanf("%s", s2[i]);

		solve();
	}

	return 0;
}

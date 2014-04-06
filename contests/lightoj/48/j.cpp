/**
 * LightOJ Contest #48: IIUPC - 2011
 *
 * Problem J: The Lost Symbol
 *
 * Keywords:
 *   - ad-hoc
 */

#include <cstdio>
#include <cstring>


#define MAXN 20

const int MAXLEN = MAXN*MAXN + 1;

#define Clr(m) memset(m, 0, sizeof(m))


int grid[MAXN][MAXN];
char txt[MAXLEN];
char sol[MAXLEN];

bool used[MAXLEN];


int N, N2;


bool is_magic()
{
	Clr(used);

	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j) {
			int n = grid[i][j];

			if (n < 1 || n > N2 || used[n]) return false;
			used[n] = true;
		}

	int magic = 0;

	for (int i = 0; i < N; ++i)
		magic += grid[i][i];

	int sum = 0;
	for (int i = 0; i < N; ++i)
		sum += grid[i][N - i - 1];

	if (sum != magic) return false;

	for (int row = 0; row < N; ++row) {
		sum = 0;

		for (int col = 0; col < N; ++col)
			sum += grid[row][col];

		if (sum != magic) return false;
	}

	for (int col = 0; col < N; ++col) {
		sum = 0;

		for (int row = 0; row < N; ++row)
			sum += grid[row][col];

		if (sum != magic) return false;
	}

	return true;
}

void solve()
{
	if (! is_magic()) {
		puts("NOT A MAGIC SQUARE");
		return;
	}

	for (int i = 0, p = 0; i < N; ++i)
		for (int j = 0; j < N; ++j, ++p)
			sol[grid[i][j] - 1] = txt[p];

	sol[N2] = 0;
	puts(sol);
}

int main()
{
	while (true) {
		if (scanf("%d", &N) != 1) break;
		N2 = N*N;

		for (int i = 0; i < N; ++i)
			for (int j = 0; j < N; ++j)
				scanf("%d", &grid[i][j]);
		gets(txt);
		gets(txt);

		solve();
	}

	return 0;
}

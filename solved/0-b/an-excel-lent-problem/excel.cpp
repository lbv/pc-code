#include <algorithm>
#include <cstdio>
using namespace std;


#define MAXDIG 9


char col[MAXDIG + 1];
int R, C;


void solve()
{
	int len = 0;

	while (C != 0) {
		int v = C % 26;
		C /= 26;

		char d;
		if (v == 0) {
			d = 'Z';
			--C;
		}
		else
			d = 'A' - 1 + v;

		col[len++] = d;
	}
	col[len] = 0;
	for (int i = 0, j = len - 1; i < j; ++i, --j)
		swap(col[i], col[j]);
}

int main()
{
	while (true) {
		scanf(" R%dC%d", &R, &C);
		if (R == 0) break;

		solve();
		printf("%s%d\n", col, R);
	}

	return 0;
}

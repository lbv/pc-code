#include <algorithm>
#include <cstdio>
using namespace std;


int g[5][5];
int l[5];
int perm[5] = { 0, 1, 2, 3, 4 };


int solve()
{
	int best = 0;

	do {
		for (int i = 0; i < 5; ++i)
			l[i] = perm[i];

		int cur = g[l[0]][l[1]] + g[l[1]][l[0]] +
			g[l[1]][l[2]] + 2*g[l[2]][l[3]] + g[l[2]][l[1]] +
			2*g[l[3]][l[2]] + 2*g[l[3]][l[4]] + 2*g[l[4]][l[3]];

		if (cur > best) best = cur;
	} while (next_permutation(perm, perm + 5));

	return best;
}

int main()
{
	for (int i = 0; i < 5; ++i)
		for (int j = 0; j < 5; ++j)
			scanf("%d", &g[i][j]);

	printf("%d\n", solve());

	return 0;
}

/**
 * LightOJ Contest #477: Exam Ending Contest
 *
 * Problem A: Magician
 *
 * Keywords:
 *   - ad-hoc
 *   - grid
 */

#include <cstdio>


int a1[4][4];
int a2[4][4];
int x1, x2;



void solve()
{
	int cnt = 0;
	int num;

	for (int i = 0; i < 4; ++i) {
		int a = a1[x1-1][i];

		for (int j = 0; j < 4; ++j) {
			int b = a2[x2-1][j];
			if (a == b) ++cnt, num = a;
		}
	}

	if (cnt == 1)
		printf("%d\n", num);
	else if (cnt > 1)
		puts("Bad magician!");
	else
		puts("Volunteer cheated!");
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d", &x1);
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j) scanf("%d", &a1[i][j]);
		scanf("%d", &x2);
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j) scanf("%d", &a2[i][j]);
		printf("Case #%d: ", ++ncase);
		solve();
	}

	return 0;
}

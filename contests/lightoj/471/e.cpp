/**
 * LightOJ Contest #471: AIUB Practice Contest
 *
 * Problem E: Energy Level
 *
 * Keywords:
 *   - binary search
 */

#include <cstdio>


#define MAXN 500


int N;
int a[MAXN];
int lo, hi;


bool pass(int e)
{
	for (int i = 0; i < N; ++i) {
		if (a[i] <= e) continue;
		if (a[i] > 2*e) return false;
		--e;
	}

	return true;
}

int solve()
{
	lo = 1;

	while (lo <= hi) {
		int md = (lo+hi) / 2;

		bool a = pass(md);
		bool b = pass(md-1);

		if (a && !b) return md;

		if (a && b) hi = md-1;
		else lo = md + 1;
	}

	return -1;
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d", &N);

		hi = 0;
		for (int i = 0; i < N; ++i) {
			scanf("%d", &a[i]);
			if (a[i] > hi) hi = a[i];
		}

		printf("Case %d: %d\n", ++ncase, solve());
	}

	return 0;
}

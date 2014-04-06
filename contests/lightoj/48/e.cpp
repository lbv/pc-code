/**
 * LightOJ Contest #48: IIUPC - 2011
 *
 * Problem E: Gender Equity
 *
 * Keywords:
 *   - ad-hoc
 *   - arrays
 */

#include <algorithm>
#include <cstdio>
using namespace std;


int N, M, X, K;

int sum1, sum2;
int sub1, sub2;  // how much can be subtracted from group 1 or 2


void solve()
{
	int num;
	bool possible = true;

	sum1 = sub1 = 0;
	for (int i = 0; i < N; ++i) {
		scanf("%d", &num);

		sum1 += num;
		sub1 += min(K, num - X);
		if (num < X) possible = false;
	}

	sum2 = sub2 = 0;
	for (int i = 0; i < M; ++i) {
		scanf("%d", &num);

		sum2 += num;
		sub2 += min(K, num - X);
		if (num < X) possible = false;
	}

	if (sum1 < sum2) {
		swap(sum1, sum2);
		swap(sub1, sub2);
	}

	if (sum1 - sum2 > sub1) possible = false;

	if (! possible) {
		puts("Impossible");
		return;
	}

	sub1 -= sum1 - sum2;
	sum2 -= min(sub1, sub2);

	printf("%d\n", sum2);
}

int main()
{
	int T;
	scanf("%d", &T);

	while (T--) {
		scanf("%d%d%d%d", &N, &M, &X, &K);

		solve();
	}

	return 0;
}

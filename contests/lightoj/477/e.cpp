/**
 * LightOJ Contest #477: Exam Ending Contest
 *
 * Problem E: Fair Play
 *
 * Keywords:
 *	 - greedy
 */

#include <algorithm>
#include <cstdio>
using namespace std;


#define MAXN 10


int N;


double ns[MAXN];
double ks[MAXN];


int dwar()
{
	int ans = 0;

	for (int i = 0, j = 0; i < N; ++i)
		if (ns[i] > ks[j]) ++ans, ++j;

	return ans;
}

int war()
{
	int ans = 0;

	for (int i = N - 1, j = N - 1; i >= 0; --i)
		if (ns[i] > ks[j]) ++ans;
		else --j;

	return ans;
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d", &N);
		for (int i = 0; i < N; ++i) scanf("%lf", &ns[i]);
		for (int i = 0; i < N; ++i) scanf("%lf", &ks[i]);

		sort(ns, ns + N);
		sort(ks, ks + N);

		/*
		for (int i = 0; i < N; ++i) printf("  %.3lf", ns[i]); puts("");
		for (int i = 0; i < N; ++i) printf("  %.3lf", ks[i]); puts("");
		*/

		printf("Case #%d: %d %d\n", ++ncase, dwar(), war());
	}

	return 0;
}

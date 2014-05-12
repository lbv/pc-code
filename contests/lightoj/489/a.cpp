/**
 * LightOJ Contest #489: BUBT Codehacker Monthly Contest May-14
 *
 * Problem A: Mr. Toothless and His GCD Operation
 *
 * Keywords:
 *   - gcd
 *   - ad-hoc
 */

#include <cstdio>


#define MAXN 1000000



int lo[MAXN + 1];  // lo[i]: lowest prime factor of i
bool vis[MAXN + 1];

int bestg[MAXN + 1];  // best[i]: highest GCD(a,b) in range [2:i]
int bestb[MAXN + 1];  // best[i]: value of b for bestg[i]

int N;


void prepare()
{
	for (int i = 2; i <= MAXN; ++i)
		if (! vis[i])
			for (int j = i; j <= MAXN; j += i) {
				vis[j] = true;
				if (lo[j] == 0)
					lo[j] = i;
			}

	bestg[2] = 1;
	bestb[2] = 2;
	for (int i = 3; i <= MAXN; ++i) {
		bestg[i] = bestg[i-1];
		bestb[i] = bestb[i-1];

		int g = i/lo[i];
		if (g >= bestg[i])
			bestg[i] = g, bestb[i] = i;
	}
}

int main()
{
	prepare();

	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d", &N);

		int b = bestb[N];
		int a = b / lo[b];

		if (a == 1) a = b-1;
		printf("Case %d: %d %d\n", ++ncase, a, b);
	}

	return 0;
}

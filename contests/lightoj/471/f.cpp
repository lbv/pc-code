/**
 * LightOJ Contest #471: AIUB Practice Contest
 *
 * Problem F: Flappy Bird
 *
 * Keywords:
 *   - dynamic programming
 */

#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;


#define MAXN 500
#define MAXE 500

#define Neg(m) memset(m, -1, sizeof(m))


const int MAXN2 = MAXN/2;


int N, K, Q;
int P[MAXN2];
int E[MAXN2];

int memo[MAXN2][MAXE + 1];


// dp(p, e): maximum number of points for pillars [p : N) using e energy
int dp(int p, int e)
{
	if (memo[p][e] >= 0) return memo[p][e];

	if (p >= N) return 0;

	int best = dp(p + 1, e);

	if (e >= E[p])
		best = max(best, P[p]*E[p] + dp(p+1, e-E[p]));

	return memo[p][e] = best;
}

int solve()
{
	Neg(memo);

	return dp(0, Q) + (N + 1) * K;
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d%d%d", &N, &K, &Q);
		N /= 2;
		for (int i = 0; i < N; ++i) scanf("%d%d", &P[i], &E[i]);

		printf("Case %d: %d\n", ++ncase, solve());
	}

	return 0;
}

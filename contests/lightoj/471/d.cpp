/**
 * LightOJ Contest #471: AIUB Practice Contest
 *
 * Problem D: Hippo Circus
 *
 * Keywords:
 *   - greedy
 */

#include <algorithm>
#include <cstdio>
using namespace std;


#define MAXN 100000


int N, H, Ta, Td;
int hs[MAXN];


int solve()
{
	if (Td >= Ta*2) return Ta*N;

	int ans = 0;
	sort(hs, hs + N);

	int lt = 0, rt = N - 1;
	while (lt <= rt) {
		int j;
		for (j = rt; j > lt && hs[lt] + hs[j] >= H; --j);

		if (j == lt) {
			ans += Ta * (rt - lt + 1);
			break;
		}

		ans += Ta * (rt - j) + Td;

		++lt;
		rt = j - 1;
	}

	return ans;
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d%d%d%d", &N, &H, &Ta, &Td);
		for (int i = 0; i < N; ++i) scanf("%d", &hs[i]);

		printf("Case %d: %d\n", ++ncase, solve());
	}

	return 0;
}

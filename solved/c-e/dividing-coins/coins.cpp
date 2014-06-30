#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;


#define MAXM 100
#define MAXC 500

#define INF 0x3f3f3f3f


const int MAXSUM = MAXC * MAXM/2;


int coins[MAXM];
int m;

bool dp1[MAXSUM + 1], dp2[MAXSUM + 2];
bool *p1, *p2;


int solve()
{
	p1 = dp1, p2 = dp2;
	p1[0] = true;
	int lo = 0, hi = 0;

	for (int i = 0; i < m; ++i) {
		int hi2 = -1, lo2 = INF;
		int c = coins[i];

		memset(p2, 0, sizeof(bool) * (MAXSUM + 1));

		for (int v = lo; v <= hi; ++v) {
			if (! p1[v]) continue;
			int v2;

			v2 = v+c;
			if (v2 <= MAXSUM) {
				p2[v2] = true;
				if (v2 > hi2) hi2 = v2;
				if (v2 < lo2) lo2 = v2;
			}
			v2 = abs(v-c);
			if (v2 <= MAXSUM) {
				p2[v2] = true;
				if (v2 > hi2) hi2 = v2;
				if (v2 < lo2) lo2 = v2;
			}
		}

		swap(p1, p2);
		hi = hi2, lo = lo2;
	}

	for (int i = lo; i <= hi; ++i)
		if (p1[i]) return i;
	return -1;
}

int main()
{
	int n;
	scanf("%d", &n);

	while (n--) {
		scanf("%d", &m);
		for (int i = 0; i < m; ++i) scanf("%d", &coins[i]);
		printf("%d\n", solve());
	}

	return 0;
}

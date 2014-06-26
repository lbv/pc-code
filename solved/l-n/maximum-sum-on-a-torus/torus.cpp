#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;


#define MAXN 75

#define Clr(m) memset(m, 0, sizeof(m))


int N;
int M[2*MAXN][MAXN];

int cs[MAXN];  // cumulative sums of columns


int solve()
{
	int ans = 0;

	for (int i = 0; i < N; ++i) {
		Clr(cs);

		for (int h = 1; h <= N; ++h) {
			int lo = 0, hi = 0;

			int total = 0, total_hi = 0, total_lo = 0;

			for (int j = 0; j < N; ++j) {
				cs[j] += M[i + h - 1][j];

				total += cs[j];

				hi = hi + cs[j] < 0 ? 0 : hi + cs[j];
				lo = lo + cs[j] > 0 ? 0 : lo + cs[j];

				total_hi = max(total_hi, hi);
				total_lo = min(total_lo, lo);
			}

			int row = max(total_hi, total - total_lo);
			ans = max(ans, row);
		}

	}

	return ans;
}

int main()
{
	int T;
	scanf("%d", &T);

	while (T--) {
		scanf("%d", &N);

		for (int i = 0; i < N; ++i)
			for (int j = 0; j < N; ++j) {
				scanf("%d", &M[i][j]);
				M[i + N][j] = M[i][j];
			}

		printf("%d\n", solve());
	}

	return 0;
}

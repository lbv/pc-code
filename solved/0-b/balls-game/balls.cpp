#include <algorithm>
#include <cstdio>
using namespace std;


#define MAXN 100


int n, k, x;
int balls[MAXN];


int simulate(int i)
{
	int a = i;
	int b = i + 1;

	int ball = balls[i];

	int total = 0;
	for (int j = 0; true; ++j) {
		int cnt = j == 0 ? 1 : 0;

		for (; a >= 0 && balls[a] == ball; --a) ++cnt;
		for (; b < n  && balls[b] == ball; ++b) ++cnt;

		if (cnt >= 3) total += cnt;
		else break;

		if (a >= 0 && b < n && balls[a] == balls[b])
			ball = balls[a];
		else break;
	}

	return total - 1;
}

int solve()
{
	int ans = 0;

	for (int i = 0; i < n; ++i)
		if (balls[i] == x) {
			ans = max(ans, simulate(i));
			while (i < n && balls[i] == x) ++i;
			--i;
		}

	return ans;
}

int main()
{
	scanf("%d%d%d", &n, &k, &x);
	for (int i = 0; i < n; ++i) scanf("%d", &balls[i]);

	printf("%d\n", solve());

	return 0;
}

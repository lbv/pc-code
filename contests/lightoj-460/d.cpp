#include <algorithm>
#include <cstdio>
using namespace std;


typedef long long i64;


i64 m;


bool solve()
{
	i64 lo = 1;
	i64 hi = min(m, 1000000LL);

	while (lo <= hi) {
		i64 n = (hi + lo) / 2;

		i64 x = n*(n+1)*(n+2);

		if (x == m) return true;
		if (x < m) lo = n + 1;
		else hi = n - 1;
	}
	return false;
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%lld", &m);
		printf("Case %d: ", ++ncase);
		if (solve())
			puts("Yes");
		else
			puts("No");
	}

	return 0;
}

#include <algorithm>
#include <cstdio>
using namespace std;


int a, b, c;


int solve()
{
	if (a > b) swap(a, b);
	if (a > c) swap(a, c);
	if (b > c) swap(b, c);
	return b;
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d%d%d", &a, &b, &c);
		printf("Case %d: %d\n", ++ncase, solve());
	}

	return 0;
}

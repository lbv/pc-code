#include <cstdio>


#define MAXN 200000


int n, t, c;
int ss[MAXN];  // crime severities


int solve()
{
	int cnt = 0;

	int e = 0;  // number of severe criminals in current window
	for (int i = 0, I = c-1; i < I; ++i)
		if (ss[i] > t) ++e;

	for (int i = 0, j = c-1; j < n; ++i, ++j) {
		if (ss[j] > t) ++e;

		if (e == 0) ++cnt;

		if (ss[i] > t) --e;
	}

	return cnt;
}

int main()
{
	scanf("%d%d%d", &n, &t, &c);
	for (int i = 0; i < n; ++i) scanf("%d", &ss[i]);
	printf("%d\n", solve());

	return 0;
}

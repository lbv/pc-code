#include <cstdio>


#define MAXN 50


int n, k;
int ss[MAXN + 1];


int solve()
{
	int ans = 0;

	for (int i = 1; i <= n && ss[i] >= ss[k] && ss[i] > 0; ++i)
		++ans;

	return ans;
}

int main()
{
	scanf("%d%d", &n, &k);

	for (int i = 1; i <= n; ++i) scanf("%d", &ss[i]);
	printf("%d\n", solve());

	return 0;
}

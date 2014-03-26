#include <cstdio>


int n;


void solve()
{
	if (n == 1) {
		puts("2");
		return;
	}

	putchar('4');
	for (int i = 2; i < n; ++i) putchar('9');
	puts("7");
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d", &n);
		printf("Case %d: ", ++ncase);
		solve();
	}

	return 0;
}

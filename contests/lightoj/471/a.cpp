#include <cstdio>


int R, B;


double solve()
{
	return 6.0 / B * R;
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d%d", &R, &B);
		printf("Case %d: ", ++ncase);

		if (B == 0) puts("-1");
		else printf("%.2lf\n", solve());
	}

	return 0;
}

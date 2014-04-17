/**
 * LightOJ Contest #477: Exam Ending Contest
 *
 * Problem B: Game of Cookie
 *
 * Keywords:
 *	 - brute force
 *	 - math
 */

#include <cstdio>


#define MAX_FACT 100001


double C, F, X;

double sums[MAX_FACT];


double cookies(int x)
{
	sums[x] = sums[x-1] + C / (2 + F*(x-1));

	return sums[x] + X / (2 + x*F);
}

double solve()
{
	double ans = X/2;

	for (int i = 1; true; ++i) {
		double tmp = cookies(i);
		if (tmp < ans)
			ans = tmp;
		else if (tmp > ans)
			break;

	}
	return ans;
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%lf%lf%lf", &C, &F, &X);
		printf("Case #%d: %.7lf\n", ++ncase, solve() + 1e-10);
	}

	return 0;
}

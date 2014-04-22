#include <cmath>
#include <cstdio>


const double pi = acos(-1);


double r;


double solve()
{
	double r2 = r*r;
	return r2*(4 - pi);
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%lf", &r);
		printf("Case %d: %.2lf\n", ++ncase, solve() + 1e-9);
	}

	return 0;
}

#include <cmath>
#include <cstdio>


const double pi = acos(-1.0);


double R;
int n;


double solve()
{
    return R / (1/sin(pi/n) + 1);
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%lf%d", &R, &n);
		printf("Case %d: %.9lf\n", ++ncase, solve());
	}

	return 0;
}

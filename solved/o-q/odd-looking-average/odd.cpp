#include <cmath>
#include <cstdio>


int k;
double a, b;


double antider(double x)
{
	return pow(x, k+1) / (k+1);
}

double solve()
{
	if (a == b) return pow(a, k);

	return (antider(b) - antider(a)) / (b-a);
}

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%d%lf%lf", &k, &a, &b);
		printf("Case %d: %.9lf\n", ++ncase, solve());
	}

	return 0;
}

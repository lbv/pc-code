#include <cmath>
#include <cstdio>


#define EPS (1e-9)


const double pi = acos(-1);


double r;
int n;


double solve()
{
	double ang = pi/n;
	double b = sin(ang)*r;
	double h = cos(ang)*r;
	return b*h*n;
}

int main()
{
	while (scanf("%lf%d", &r, &n) == 2) {
		printf("%.3lf\n", solve() + EPS);
	}

	return 0;
}

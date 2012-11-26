#include <cmath>
#include <cstdio>


#define EPS (1e-9)


double a;
double X, Y, Z;

const double Pi = acos(0.0) * 2;
const double Sqr3 = sqrt(3);


void solve()
{
    Z = a*a * (1.0 - Pi/6 - Sqr3/4);
    Y = a*a/4.0 * (4 - Pi) - 2*Z;
    X = a*a - 4*Y - 4*Z;
}

int main()
{
    while (true) {
        if (scanf("%lf", &a) != 1) break;

        solve();
        printf("%.3lf %.3lf %.3lf\n", X + EPS, 4*Y + EPS, 4*Z + EPS);
    }

    return 0;
}

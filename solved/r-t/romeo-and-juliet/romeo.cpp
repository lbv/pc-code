#include <cmath>
#include <cstdio>


#define EPS (1e-9)

const double pi = acos(-1);


double x_1, y_1, x_2, y_2, a, b;


double solve()
{
    double dx = x_1 - x_2, dy = y_1 - y_2;
    double l  = sqrt(dx*dx + dy*dy);
    return l / tan(a/180*pi) + l / tan(b/180*pi) + EPS;
}

int main()
{
    while (true) {
        if (scanf("%lf%lf%lf%lf%lf%lf", &x_1, &y_1, &x_2, &y_2, &a, &b) != 6)
            break;
        printf("%.3lf\n", solve());
    }

    return 0;
}

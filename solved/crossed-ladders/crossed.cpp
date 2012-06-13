#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;

#define EPS (1e-6)

double X, Y, L, c;

void solve()
{
    double lo = 0.0;
    double hi = min(X, Y);

    double prev = -1.0;

    double x, y, a, b, alpha, beta;

    while (true) {
        L = (lo + hi) / 2.0;
        if (fabs(L - prev) < EPS) break;

        alpha = acos(L / X);
        beta = acos(L / Y);

        a = X * sin(alpha);
        b = Y * sin(beta);

        x = c*X / a;
        y = c*Y / b;

        if (x*cos(alpha) + y*cos(beta) > L) hi = L;
        else lo = L;
        prev = L;
    }
}

int main()
{
    while (true) {
        if (scanf("%lf%lf%lf", &X, &Y, &c) != 3) break;

        solve();
        printf("%.3lf\n", L);
    }

    return 0;
}

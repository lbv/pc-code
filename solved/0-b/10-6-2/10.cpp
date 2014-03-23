#include <cmath>
#include <cstdio>


#define EPS (1e-9)


const double pi = acos(-1);


int    L;
double ar, ag;  // red and green areas


void solve()
{
    double r = 1.0 * L / 5;
    ar = pi * r * r + EPS;

    double w = 3.0 * L / 5;
    ag = w * L - ar + EPS;
}

int main()
{
    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%d", &L);
        solve();
        printf("%.2lf %.2lf\n", ar, ag);
    }

    return 0;
}

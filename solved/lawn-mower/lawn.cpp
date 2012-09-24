#include <algorithm>
#include <cstdio>
using namespace std;


#define MAXN 1000
#define MAXX 75.0
#define MAXY 100.0
#define EPS  (1e-9)


int nx, ny;
double w;

double xs[MAXN];
double ys[MAXN];


bool eps_less(double a, double b) { return b - a > EPS; }
bool solve()
{
    double hi = 0.0;
    double half = w/2.0;

    sort(xs, xs + nx);

    for (int i = 0; i < nx && eps_less(hi, MAXX); ++i) {
        if (eps_less(hi, xs[i] - half))
            return false;
        hi = xs[i] + half;
    }

    if (eps_less(hi, MAXX)) return false;

    hi = 0.0;

    sort(ys, ys + ny);
    for (int i = 0; i < ny && eps_less(hi, MAXY); ++i) {
        if (eps_less(hi, ys[i] - half))
            return false;
        hi = ys[i] + half;
    }

    if (eps_less(hi, MAXY)) return false;

    return true;
}

int main()
{
    while (true) {
        scanf("%d%d%lf", &nx, &ny, &w);
        if (nx == 0) break;

        for (int i = 0; i < nx; ++i) scanf("%lf", &xs[i]);
        for (int i = 0; i < ny; ++i) scanf("%lf", &ys[i]);

        if (solve())
            puts("YES");
        else
            puts("NO");
    }

    return 0;
}

#include <cmath>
#include <cstdio>

#define EPS (1e-9)

int n;
double dx, dy;
double gx, gy;
double x, y;

bool eps_less(double a, double b) { return b - a > EPS; }

bool can_escape()
{
    double dist_dog = sqrt((dx - x)*(dx - x) + (dy - y)*(dy - y));
    double dist_gop = sqrt((gx - x)*(gx - x) + (gy - y)*(gy - y));

    return ! eps_less(dist_dog, dist_gop * 2);
}

int main()
{
    while (true) {
        if (scanf("%d%lf%lf%lf%lf", &n, &gx, &gy, &dx, &dy) != 5) break;

        bool escaped = false;
        while (n--) {
            if (escaped) {
                scanf("%*f%*f");
                continue;
            }

            scanf("%lf%lf", &x, &y);
            if (can_escape()) {
                printf("The gopher can escape through "
                       "the hole at (%.3lf,%.3lf).\n", x, y);
                escaped = true;
            }
        }

        if (! escaped)
            puts("The gopher cannot escape.");
    }

    return 0;
}

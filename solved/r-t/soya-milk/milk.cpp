#include <cmath>
#include <cstdio>


#define EPS (1e-8)


int l, w, h, theta;
const double pi = acos(-1);


double solve()
{
    double an  = theta * pi / 180.0;  // theta in radians
    double anc = pi/2.0 - an;         // complementary angle

    double a;  // 2D area of milk
    double y1 = sin(anc)*h;
    double y2 = sin(an)*l;

    if (y1 >= y2) {
        double s = tan(an)*l;
        a = s*l/2.0 + (h-s)*l;
    }
    else {
        double s = tan(anc)*h;
        a = s*h/2.0;
    }

    return a * w + EPS;
}

int main()
{
    while (true) {
        if (scanf("%d%d%d%d", &l, &w, &h, &theta) != 4) break;
        printf("%.3lf mL\n", solve());
    }

    return 0;
}

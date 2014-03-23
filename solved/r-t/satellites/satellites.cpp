#include <cmath>
#include <cstdio>


#define EPS (1e-9)


const double Pi = acos(0) * 2.0;

int s, a;
char unit[8];
double r, ang;
double arc, chord;


void solve()
{
    r = 6440 + s;

    if (unit[0] == 'd') a %= 360;
    else a %= (360*60);

    ang = a * Pi / 180.0;
    if (unit[0] == 'm') ang /= 60.0;

    if (ang > Pi) ang = 2*Pi - ang;

    arc = r*ang;
    chord = 2*r*sin(ang / 2.0);
}

int main()
{
    while (true) {
        if (scanf("%d%d%s", &s, &a, unit) != 3) break;

        solve();
        printf("%.6lf %.6lf\n", arc + EPS, chord + EPS);
    }

    return 0;
}

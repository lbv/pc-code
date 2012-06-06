#include <cstdio>
#include <cmath>

#define EPS (1e-9)

int a, b;
double L, W;

void binsearch()
{
    double Lprev = -1;
    double Wprev = -1;
    double Lmin = 0.0;
    double Lmax = 210.0;

    double f1 = 1.0 * b / a;
    double ha;  // half of the angle for the arcs
    double r;   // radius of circle
    double S;   // arc
    double P;   // perimeter

    while (true) {
        L = (Lmin + Lmax) / 2.0;
        W = L * f1;
        if (fabs(Lprev - L) < EPS && fabs(Wprev - W)) break;

        ha = atan(W/L);
        r = W / (sin(ha)*2);
        S = r * ha * 2;
        P = 2*L + 2*S;

        if (P > 400.0) Lmax = L;
        else Lmin = L;
        Lprev = L;
        Wprev = W;
    }
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d : %d", &a, &b);
        binsearch();
        printf("Case %d: %.8lf %.8lf\n", ++ncase, L, W);
    }

    return 0;
}

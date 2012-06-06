#include <cstdio>
#include <cstdlib>

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        int Ax, Ay, Bx, By, Cx, Cy, Dx, Dy;
        scanf("%d%d%d%d%d%d", &Ax, &Ay, &Bx, &By, &Cx, &Cy);

        int dx = Bx - Ax;
        int dy = By - Cy;

        Dx = Cx - dx;
        Dy = Ay - dy;

        // vectors to calculate cross product
        int Ux, Uy, Vx, Vy;
        Ux = Bx-Ax;
        Uy = By-Ay;
        Vx = Dx-Ax;
        Vy = Dy-Ay;

        int area = abs(Ux*Vy - Uy*Vx);

        printf("Case %d: %d %d %d\n", ++ncase, Dx, Dy, area);
    }

    return 0;
}

#include <cstdio>

int H, U, D, F;
int day;

bool solve()
{
    day = 1;

    double goal = H;
    double u = U;
    double d = D;
    double f = 1.0*U*F/100.0;

    double h = 0;

    while (true) {
        h += u;
        if (h > goal) return true;

        h -= d;
        if (h < 0) return false;

        u -= f;
        if (u < 0) u = 0;
        ++day;
    }
}

int main()
{
    while (true) {
        scanf("%d%d%d%d", &H, &U, &D, &F);
        if (H == 0) break;

        if (solve())
            printf("success on day %d\n", day);
        else
            printf("failure on day %d\n", day);
    }

    return 0;
}

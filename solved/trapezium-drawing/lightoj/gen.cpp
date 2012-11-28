#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 1
#define MAXT 500
#define MINCOORD -10000
#define MAXCOORD 10000
#define MAXLEN   10000
#endif

#if 0
#define MAXT 20
#define MINCOORD -100
#define MAXCOORD 100
#define MAXLEN   50
#endif


const int DiffCoord = MAXCOORD - MINCOORD + 1;
const double Pi_2 = acos(0.0);


void test_case()
{
    int Ax, Ay, Bx, By;
    int a, b, c, d;
    double da, bas;

    do {
        Ax = rand() % DiffCoord + MINCOORD;
        Ay = rand() % DiffCoord + MINCOORD;
        Bx = rand() % DiffCoord + MINCOORD;
        By = rand() % DiffCoord + MINCOORD;

        da = sqrt((By - Ay) * (By - Ay) + (Bx - Ax) * (Bx - Ax));
        a = da;
    } while (a < 3);

    do {
        c = rand() % (a - 1) + 1;
        bas = da - c;
    } while (bas >= MAXLEN - 3);

    do {
        b = rand() % MAXLEN + 1;
        d = rand() % MAXLEN + 1;
    } while (b + d <= bas || bas + b <= d || bas + d <= b);

    printf("%d %d %d %d %d %d %d\n", Ax, Ay, Bx, By, b, c, d);
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    while (T--) test_case();

    return 0;
}

#include <cstdio>
#include <cstdlib>
#include <ctime>

#define MAXT 1000

#define MAXV 1000
#define MAXD 10000

void test_case()
{
    int vi = rand() % MAXV + 1;
    int ui = rand() % vi;
    int di = rand() % (MAXD + 1);
    int ai = rand() % (di + 1);

    double v = vi, u = ui, d = di, a = ai;
    v /= 10.0;
    u /= 10.0;
    d /= 10.0;
    a /= 10.0;
    printf("%.1lf %.1lf %.1lf %.1lf\n", v, u, d, a);
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    while (T--) test_case();

    return 0;
}

#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 25
#define MAXN 100
#define MAXD 100000
#define MINX -10000
#define MAXX 10000
#define MAXP 10
#define MAXM 200
#define NL   0
#endif

#if 1
#define MAXT 20
#define MAXN 20
#define MAXD 110
#define MINX -100
#define MAXX 100
#define MAXP 10
#define MAXM 15
#define NL   1
#endif


const int XRange = MAXX - MINX + 1;


void test_case(bool crit = false)
{
    int N = crit ? MAXN : rand() % MAXN + 1;
    int Di = rand() % (MAXD * 10 + 1);
    double D = Di;
    D /= 10.0;

#if NL
    puts("");
#endif

    printf("%d %.1lf\n", N, D);
    while (N--) {
        int x = rand() % XRange + MINX;
        int y = rand() % XRange + MINX;
        int n = rand() % (MAXP + 1);
        int m = rand() % MAXM + 1;
        printf("%d %d %d %d\n", x, y, n, m);
    }
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    test_case(true); --T;
    while (T--) test_case();

    return 0;
}

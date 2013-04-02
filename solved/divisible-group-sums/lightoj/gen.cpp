#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 20
#define MAXN 200
#define MAXQ 10
#define MAXD 20
#define MAXM 10
#endif

#if 1
#define MAXT 20
#define MAXN 100
#define MAXQ 10
#define MAXD 20
#define MAXM 10
#define NL   1
#endif


void test_case(bool crit = false)
{
#if NL
    puts("");
#endif

    int N = crit ? MAXN : rand() % MAXN + 1;
    int Q = crit ? MAXQ : rand() % MAXQ + 1;
    printf("%d %d\n", N, Q);

    while (N--) {
        int n, z;
        z = rand() % 15;
        if      (z < 2) n = rand() % 1000;
        else if (z < 5) n = rand() % 1000000;
        else            n = rand();

        printf("%d\n", n);
    }

    while (Q--) {
        int D = rand() % MAXD + 1;
        int M = rand() % MAXM + 1;
        printf("%d %d\n", D, M);
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

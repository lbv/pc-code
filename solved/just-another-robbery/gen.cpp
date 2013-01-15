#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 100
#define MAXN 100
#define MAXM 100
#define EXTRA_NL 0
#endif

#if 20
#define MAXT 20
#define MAXN 7
#define MAXM 100
#define EXTRA_NL 1
#endif


double rand_p()
{
    int intp = rand() % 101;

    if (rand() % 5 != 0) intp = rand() % 20;

    double p = intp;
    p /= 100.0;
    return p;
}

void test_case()
{
    double P = rand_p();
    int N = rand() % MAXN + 1;

#if EXTRA_NL
    puts("");
#endif
    printf("%.2lf %d\n", P, N);

    while (N--) {
        int M = rand() % MAXM + 1;
        double p = rand_p();
        printf("%d %.2lf\n", M, p);
    }
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    while (T--) test_case();

    return 0;
}

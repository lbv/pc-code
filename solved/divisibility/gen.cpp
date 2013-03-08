#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 100
#define MAXN 10000
#define MAXK 100
#define MAXI 10000
#define MINI -10000
#endif

#if 1
#define MAXT 20
#define MAXN 12
#define MAXK 30
#define MAXI 100
#define MINI -100
#endif


const int RangeI = MAXI - MINI + 1;


void test_case(bool crit = false)
{
    int N = crit ? MAXN : rand() % MAXN + 1;
    int K = rand() % (MAXK - 1) + 2;

    printf("%d %d\n", N, K);

    for (int i = 0; i < N; ++i) {
        if (i > 0) putchar(' ');
        int n = rand() % RangeI + MINI;
        printf("%d", n);
    }
    puts("");
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

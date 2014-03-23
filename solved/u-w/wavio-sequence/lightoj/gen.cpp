#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 12
#define MAXN 100000
#define MINI -100000000
#define MAXI 100000000
#endif

#if 1
#define MAXT 20
#define MAXN 20
#define MINI -20
#define MAXI 20
#endif


const int IRange = MAXI - MINI + 1;


void test_case(bool crit = false)
{
    int N = crit ? MAXN : rand() % MAXN + 1;
    printf("%d\n", N);

    for (int i = 0; i < N; ++i) {
        if (i > 0) putchar(' ');
        int num = rand() % IRange + MINI;
        printf("%d", num);
    }
    putchar('\n');
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

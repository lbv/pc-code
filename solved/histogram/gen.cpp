#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 20
#define MAXN 30000
#define MAXH 30000
#define NL   0
#endif

#if 1
#define MAXT 20
#define MAXN 10
#define MAXH 100
#define NL   1
#endif


void test_case(bool crit = false)
{
    int N = crit ? MAXN : rand() % MAXN + 1;

#if NL
    puts("");
#endif
    printf("%d\n", N);

    for (int i = 0; i < N; ++i) {
        if (i > 0) putchar(' ');
        int h = rand() % MAXH + 1;
        printf("%d", h);
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

#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 10
#define MAXN 10000
#define MAXC 40000
#define NL   0
#endif

#if 1
#define MAXT 10
#define MAXN 16
#define MAXC 100
#define NL   1
#endif


void test_case(bool crit = false)
{
#if NL
    puts("");
#endif

    int N = crit ? MAXN : rand() % (MAXN + 1);
    printf("%d\n", N);

    while (N--) {
        int x = rand() % MAXC;
        int y = rand() % MAXC;
        printf("%d %d\n", x, y);
    }
}

int main()
{
    srand(time(NULL));

    int T = MAXT;

    test_case(true); --T;
    while (T--) test_case();

    puts("0");

    return 0;
}

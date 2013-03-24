#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 10
#define MAXM 500
#define MAXN 500
#define MAXI 1000
#endif

#if 1
#define MAXT 20
#define MAXM 10
#define MAXN 10
#define MAXI 100
#endif


void test_case(bool crit = false)
{
    int m = crit ? MAXM : rand() % MAXM + 1;
    int n = crit ? MAXN : rand() % MAXN + 1;
    printf("\n%d %d\n", m, n);

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j > 0) putchar(' ');
            printf("%d", rand() % (MAXI + 1));
        }
        puts("");
    }
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j > 0) putchar(' ');
            printf("%d", rand() % (MAXI + 1));
        }
        puts("");
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

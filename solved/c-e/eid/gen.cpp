#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 225
#define MAXN 1000
#define MAXI 10000
#endif

#if 1
#define MAXT 20
#define MAXN 50
#define MAXI 10000
#endif


void test_case(bool crit = false)
{
    int n = crit ? MAXN : rand() % (MAXN - 1) + 2;
    printf("%d\n", n);

    for (int i = 0; i < n; ++i) {
        if (i > 0) putchar(' ');
        printf("%d", rand() % MAXI + 1);
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

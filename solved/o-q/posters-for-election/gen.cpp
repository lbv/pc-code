#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 1
#define MAXT 8
#define MAXN 100000
#endif

#if 0
#define MAXT 20
#define MAXN 2000
#endif


void test_case(bool crit = false)
{
    int n = rand() % MAXN + 1;
    if (crit) n = MAXN;

    printf("%d\n", n);
    for (int i = 0; i < n; ++i) {
        int r = rand() % (2*n) + 1;
        int l = rand() % r + 1;

        printf("%d %d\n", l, r);
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

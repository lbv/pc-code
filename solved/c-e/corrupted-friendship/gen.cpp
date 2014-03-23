#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 30
#define MAXN 100000
#endif

#if 1
#define MAXT 20
#define MAXN 20
#endif


void test_case(bool crit = false)
{
    int N = crit ? MAXN : rand() % MAXN + 1;
    printf("%d\n", N);

    for (int i = 2; i <= N; ++i) {
        int v = i;
        int u = rand() % (v - 1) + 1;
        printf("%d %d\n", u, v);
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

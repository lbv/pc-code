#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 1
#define MAXT 100
#define MAXN 1000
#define MAXM 1000000
#define MAXC 1000000
#endif

#if 0
#define MAXT 100
#define MAXN 10
#define MAXM 1000000
#define MAXC 100
#endif


void test_case()
{
    int n = rand() % MAXN + 1;
    int m = rand() % n + 1;

    if (rand() % 20 == 0)
        m = rand() % MAXM + 1;

    printf("%d %d\n", n, m);

    for (int i = 0; i < n; ++i) {
        int c = rand() % MAXC + 1;

        printf("%s%d", i == 0 ? "" : " ", c);
    }
    putchar('\n');
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    while (T--) test_case();

    return 0;
}

#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 10
#define MAXN 30000
#define MAXW 10000
#endif

#if 1
#define MAXT 25
#define MAXN 70
#define MAXW 500
#endif


void test_case()
{
    int n = rand() % (MAXN - 1) + 2;
    printf("%d\n", n);

    for (int i = 1; i < n; ++i) {
        int u = rand() % i;
        int v = i;
        int w = rand() % MAXW + 1;

        printf("%d %d %d\n", u, v, w);
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

#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 15
#define MAXN 10000
#define MAXM 100000
#endif

#if 1
#define MAXT 30
#define MAXN 15
#define MAXM 10
#endif


void test_case()
{
    int N = rand() % (MAXN - 1) + 2;
    int M = rand() % (MAXM + 1);

    printf("\n%d %d\n", N, M);
    while (M--) {
        int u, v;
        do {
            u = rand() % N + 1;
            v = rand() % N + 1;
        } while (u == v);

        printf("%d %d\n", u, v);
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

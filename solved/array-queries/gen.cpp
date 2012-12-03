#include <cstdio>
#include <cstdlib>
#include <ctime>

#if 0
#define MAXT 50
#define MAXN 100000
#define MAXQ 50000
#define MAXNUM 100000
#endif

#if 1
#define MAXT 500
#define MAXN 30
#define MAXQ 35
#define MAXNUM 1000
#endif



void test_case()
{
    int N = rand() % MAXN + 1;
    int q = rand() % MAXQ + 1;

    printf("\n%d %d\n", N, q);
    for (int i = 0; i < N; ++i)
        printf("%s%d", i == 0 ? "" : " ", rand() % (MAXNUM + 1));
    putchar('\n');

    while (q--) {
        int J = rand() % N + 1;
        int I = rand() % J + 1;

        printf("%d %d\n", I, J);
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

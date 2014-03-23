#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 125
#define MAXN 2000000000
#define MAXM 15
#define MAXI 2000000000
#endif

#if 1
#define MAXT 25
#define MAXN 2147483647
#define MAXM 10
#define MAXI 2147483647
#endif


void test_case()
{
    int N = rand() % MAXN + 1;
    int M = rand() % MAXM + 1;

    printf("%d %d\n", N, M);
    for (int i = 0; i < M; ++i) {
        if (i > 0) putchar(' ');

        int I = rand() % MAXI + 1;
        printf("%d", I);
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

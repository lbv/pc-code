#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 5
#define MAXN 50000
#endif

#if 1
#define MAXT 50
#define MAXN 18
#endif


void test_case()
{
    int n = rand() % (MAXN - 1) + 2;
    printf("%d\n", n);

    for (int i = 0; i < n; ++i) {
        int v = rand() % MAXN + 1;

        printf("%s%d", i == 0 ? "" : " ", v);
    }
    putchar('\n');
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    while (T--)
        test_case();

    return 0;
}

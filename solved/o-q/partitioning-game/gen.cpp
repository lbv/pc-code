#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 1000
#define MAXN 100
#define MAXP 10000
#endif

#if 1
#define MAXT 20
#define MAXN 8
#define MAXP 20
#endif


void test_case()
{
    int n = rand() % MAXN + 1;

    printf("%d\n", n);

    for (int i = 0; i < n; ++i) {
        if (i != 0) putchar(' ');
        int p = rand() % MAXP + 1;
        printf("%d", p);
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

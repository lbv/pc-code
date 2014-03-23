#include <cstdio>
#include <cstdlib>
#include <ctime>


#define MAXT 5
#define MAXN 100000
#define MAXI 100000000


void test_case()
{
    int n = rand() % MAXN + 1;
    int d = rand() % n + 1;
    printf("%d %d\n", n, d);

    for (int i = 0; i < n; ++i) {
        if (i > 0) putchar(' ');

        int v = rand() % (MAXI + 1);
        if (rand() % 20 == 0)
            v = rand() % 1000;

        printf(" %d", v);
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

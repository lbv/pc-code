#include <cstdio>
#include <cstdlib>
#include <ctime>


#define MAXT 8
#define MAXN 100000
#define MAXQ 10000
#define MAXI 1000


void test_case()
{
    int n = rand() % (MAXN - 1) + 2;
    int q = rand() % MAXQ + 1;

    printf("%d %d\n", n, q);

    for (int i = 0; i < n; ++i) {
        if (i > 0) putchar(' ');
        printf("%d", rand() % (MAXI + 1));
    }
    putchar('\n');

    while (q--) {
        int j = rand() % (n - 1) + 1;
        int i = rand() % j;
        printf("%d %d\n", i, j);
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

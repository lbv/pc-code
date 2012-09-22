#include <cstdio>
#include <cstdlib>
#include <ctime>

/*
#define MAXT 5
#define MAXN 100000
#define MAXQ 50000
*/

#define MAXT 10
#define MAXN 5
#define MAXQ 10


void test_case(bool crit = false)
{
    int n = rand() % (MAXN + 1);
    int q = rand() % MAXQ + 1;

    if (crit) n = MAXN, q = MAXQ;

    printf("\n%d %d\n", n, q);

    for (int i = 0; i < n; ++i) {
        if (i > 0) putchar(' ');
        printf("%d", rand());
    }
    putchar('\n');

    while (q--) {
        if (rand() % 2 == 0)
            printf("a %d\n", rand());
        else {
            int idx = n > 0 ? rand() % n + 1 : 1;
            if (rand() % 50 == 0)
                idx = rand() | 1;
            printf("c %d\n", idx);
        }
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

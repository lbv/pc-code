#include <cstdio>
#include <cstdlib>
#include <ctime>


#define MAXT 5
#define MAXN 100000
#define MAXQ 50000
#define MAXV 1000


void test_case(bool crit = false)
{
    int n = crit ? MAXN : rand() % MAXN + 1;
    int q = crit ? MAXQ : rand() % MAXQ + 1;
    printf("%d %d\n", n, q);

    for (int i = 0; i < n; ++i) {
        if (i > 0) putchar(' ');
        int v = rand() % (MAXV + 1);
        printf("%d", v);
    }
    puts("");

    for (int i = 1; i < q; ++i) {
        int t = rand() % 3;
        if (t == 0)
            printf("1 %d\n", rand() % n);
        else if (t == 1)
            printf("2 %d %d\n", rand() % n, rand() % MAXV + 1);
        else {
            int j = rand() % n;
            int i = rand() % (j + 1);
            printf("3 %d %d\n", i, j);
        }
    }
    printf("3 0 %d\n", n - 1);
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

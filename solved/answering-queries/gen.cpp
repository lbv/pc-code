#include <cstdio>
#include <cstdlib>
#include <ctime>

/*
#define MAXT 5
#define MAXN 100000
#define MAXQ 100000
#define MAXI 1000000
*/


#define MAXT 20
#define MAXN 100000
#define MAXQ 30
#define MAXI 1000000


void test_case()
{
    int n = rand() % MAXN + 1;
    int q = rand() % MAXQ + 1;
    printf("%d %d\n", n, q);

    for (int i = 0; i < n; ++i) {
        if (i > 0) putchar(' ');
        printf("%d", rand() % (MAXI + 1));
    }
    putchar('\n');

    int last = 0;
    for (int i = 1; i < q; ++i) {
        int type = rand() % 2;

        if (last == 1 || i == q - 1)
            type = 0;

        if (type == 0) {
            int x = rand() % n;
            int v = rand() % (MAXI + 1);
            printf("0 %d %d\n", x, v);
        }
        else
            puts("1");

        last = type;
    }
    puts("1");
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    while (T--) test_case();

    return 0;
}

#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 5
#define MAXN 100000
#define MAXQ 50000
#define MAXV 10000
#define NL   0
#endif

#if 1
#define MAXT 20
#define MAXN 64
#define MAXQ 12
#define MAXV 100
#define NL   1
#endif


void test_case()
{
    int n = rand() % MAXN + 1;
    int q = rand() % MAXQ + 1;
#if NL
    puts("");
#endif
    printf("%d %d\n", n, q);

    --q;
    while (q--) {
        int op = rand() % 2 + 1;
        int j = rand() % n;
        int i = rand() % (j + 1);

        if (op == 1) {
            int v = rand() % (MAXV + 1);
            printf("1 %d %d %d\n", i, j, v);
        }
        else
            printf("2 %d %d\n", i, j);
    }
    printf("2 0 %d\n", n - 1);
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    while (T--) test_case();

    return 0;
}

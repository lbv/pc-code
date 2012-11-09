#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 5
#define MAXN 100000
#define MAXND 250000
#define MINX -100000
#define MAXX 100000
#endif

#if 1
#define MAXT 5
#define MAXN 10
#define MAXND 100
#define MINX -50
#define MAXX 50
#endif


const int XRange = MAXX - MINX + 1;

void test_case()
{
    int N = rand() % MAXN + 1;
    printf("%d\n", N);

    for (int i = 1; i < N; ++i) {
        int op = rand() % 4;
        int nd = rand() % MAXND + 1;
        int st = rand() % nd + 1;

        if (op == 0)
            printf("A %d %d\n", st, nd);
        else if (op == 1)
            printf("B %d %d\n", st, nd);
        else if (op == 2)
            printf("S %d %d\n", st, nd);
        else {
            int x = rand() % XRange + MINX;
            printf("C %d %d %d\n", st, nd, x);
        }
    }
    printf("S 1 %d\n", MAXND);
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    while (T--) test_case();

    return 0;
}

#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 12
#define MAXN 100000
#define MAXQ 10
#define MINA -100000000
#define MAXA 100000000
#endif

#if 1
#define MAXT 20
#define MAXN 12
#define MAXQ 8
#define MINA -100
#define MAXA 100
#endif


const int RangeA = MAXA - MINA + 1;


void test_case(bool crit = false)
{
    int n = rand() % MAXN + 1;
    int q = rand() % MAXQ + 1;

    if (crit) n = MAXN, q = MAXQ;

    printf("%d %d\n", n, q);

    for (int i = 0; i < n; ++i) {
        if (i > 0) putchar(' ');
        int a = rand() % RangeA + MINA;
        printf("%d", a);
    }
    putchar('\n');

    while (q--) {
        int m = rand() % n + 1;
        printf("%d\n", m);
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

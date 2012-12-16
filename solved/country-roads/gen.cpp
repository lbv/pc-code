#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 20
#define MAXN 500
#define MAXM 16000
#define MAXW 20000
#endif

#if 1
#define MAXT 20
#define MAXN 6
#define MAXM 10
#define MAXW 100
#endif


void test_case(bool crit = false)
{
    int n = rand() % (MAXN - 1) + 2;
    int m = rand() % (MAXM + 1);
    if (crit) n = MAXN, m = MAXM;
    printf("\n%d %d\n", n, m);

    while (m--) {
        int u, v, w;
        do {
            u = rand() % n;
            v = rand() % n;
        } while (u == v);
        w = rand() % MAXW + 1;

        printf("%d %d %d\n", u, v, w);
    }
    int t = rand() % n;
    printf("%d\n", t);
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

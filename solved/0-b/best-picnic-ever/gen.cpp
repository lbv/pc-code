#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 10
#define MAXK 100
#define MAXN 1000
#define MAXM 10000
#endif

#if 1
#define MAXT 20
#define MAXK 5
#define MAXN 40
#define MAXM 80
#endif


void test_case()
{
    int K = rand() % MAXK + 1;
    int N = rand() % (MAXN-1) + 2;
    int M = rand() % MAXM + 1;

    printf("%d %d %d\n", K, N, M);

    while (K--) {
        int c = rand() % N + 1;
        printf("%d\n", c);
    }

    while (M--) {
        int u, v;
        do {
            u = rand() % N + 1;
            v = rand() % N + 1;
        } while(u == v);

        printf("%d %d\n", u, v);
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

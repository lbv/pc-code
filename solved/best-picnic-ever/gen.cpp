#include <cstdio>
#include <cstdlib>
#include <ctime>

#define MAXT 10
#define MAXK 100
#define MAXN 1000
#define MAXM 10000

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

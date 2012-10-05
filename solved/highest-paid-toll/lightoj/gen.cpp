#include <cstdio>
#include <cstdlib>
#include <ctime>


#define MAXT 10

/*
#define MAXN 10000
#define MAXM 50000
#define MAXP 1000000
#define MAXC 100000
*/

#define MAXN 10
#define MAXM 25
#define MAXP 500
#define MAXC 50


void test_case()
{
    int N = rand() % (MAXN - 1) + 2;
    int M = rand() % MAXM + 1;

    int s = rand() % N + 1;
    int t = rand() % N + 1;
    int p = rand() % MAXP + 1;

    printf("%d %d %d %d %d\n", N, M, s, t, p);

    while (M--) {
        int u, v;
        do {
            u = rand() % N + 1;
            v = rand() % N + 1;
        } while (u == v);

        int c = rand() % (MAXC + 1);

        printf("%d %d %d\n", u, v, c);
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

#include <cstdio>
#include <cstdlib>
#include <ctime>

#define MAXT 10
#define MAXN 5000
#define MAXR 100000
#define MAXW 5000

//#define MAXN 10
//#define MAXR 20

void test_case()
{
    int N = rand() % (MAXN - 1) + 2;
    int R = rand() % (MAXR - N + 1) + N;
    
    printf("%d %d\n", N, R);

    int u, v, w;
    for (int i = 1; i <= N - 1; ++i) {
        u = i;
        v = i + 1;
        w = rand() % MAXR + 1;
        printf("%d %d %d\n", u, v, w);
        R--;
    }

    while (R--) {
        do {
            u = rand() % N + 1;
            v = rand() % N + 1;
        } while (u == v);

        w = rand() % MAXR + 1;
        printf("%d %d %d\n", u, v, w);
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

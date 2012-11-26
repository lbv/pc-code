#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 200
#define MAXN 1000
#define MAXM 2000
#define MAXK 5
#endif

#if 1
#define MAXT 20
#define MAXN 15
#define MAXM 8
#define MAXK 3
#endif


void test_case()
{
    int n = rand() % (MAXN - 2) + 3;
    int m = rand() % (MAXM + 1);
    int k = rand() % (MAXK + 1);

    printf("\n%d %d %d\n", n, m, k);
    while (m--) {
        int type = rand() % 4 + 1;
        int x, y;
        do {
            x = rand() % n + 1;
            y = rand() % n + 1;
        } while (x == y);

        printf("%d %d %d\n", type, x, y);
    }
    while (k--) {
        int type = rand() % 2 + 1;
        int x, y, z;
        do {
            x = rand() % n + 1;
            y = rand() % n + 1;
            z = rand() % n + 1;
        } while (x == y || x == z || y == z);

        printf("%d %d %d %d\n", type, x, y, z);
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

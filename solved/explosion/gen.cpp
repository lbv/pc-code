#include <cstdio>
#include <cstdlib>
#include <ctime>

#define MAXT 200
#define MAXN 1000
#define MAXM 2000
#define MAXK 5

void test_case()
{
    int n = rand() % (MAXN - 2) + 3;
    int m = rand() % (MAXM + 1);
    int k = rand() % (MAXK + 1);

    printf("\n%d %d %d\n", n, m, k);
    while (m--) {
        int type = rand() % 4 + 1;
        int x = rand() % n + 1;
        int y = rand() % n + 1;

        printf("%d %d %d\n", type, x, y);
    }
    while (k--) {
        int type = rand() % 2 + 1;
        int x = rand() % n + 1;
        int y = rand() % n + 1;
        int z = rand() % n + 1;

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

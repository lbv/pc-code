#include <cstdio>
#include <cstdlib>
#include <ctime>


#define MAXT 5
/*
#define MAXN 100000
#define MAXI 100000
#define MAXQ 50000
*/

#define MAXN 100000
#define MAXI 100000
#define MAXQ 50000



void test_case()
{
    int N = rand() % MAXN + 1;
    int q = rand() % MAXQ + 1;
    printf("\n%d %d\n", N, q);
    for (int i = 0; i < N; ++i) {
        if (i > 0) putchar(' ');
        printf("%d", rand() % (MAXI + 1));
    }
    putchar('\n');
    while (q--) {
        int j = rand() % N + 1;
        int i = rand() % j + 1;
        printf("%d %d\n", i, j);
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

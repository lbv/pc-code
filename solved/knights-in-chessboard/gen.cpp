#include <cstdio>
#include <cstdlib>
#include <ctime>


#define MAXT 41000
#define MAXM 200
#define MAXN 200


void test_case()
{
    int m = rand() % MAXM + 1;
    int n = rand() % MAXN + 1;
    printf("%d %d\n", m, n);
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    for (int i = 1; i <= 200; ++i)
        for (int j = 1; j <= 200; ++j)
            if (T > 0) {
                printf("%d %d\n", i, j);
                --T;
            }

    while (T--) test_case();

    return 0;
}

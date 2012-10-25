#include <cstdio>
#include <cstdlib>
#include <ctime>


#define MAXT 20
#define MAXN 30
#define MAXK 1000000000


void test_case()
{
    int n = rand() % MAXN + 1;
    int k = rand() % MAXK + 1;
    printf("%d %d\n", n, k);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j > 0) putchar(' ');
            printf("%d", rand() % 10);
        }
        putchar('\n');
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

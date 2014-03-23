#include <cstdio>
#include <cstdlib>
#include <ctime>


#define MAXT 30
#define MAXN 100
#define MAXM 100
#define MAXI 1000000


void test_case()
{
    int n = rand() % (MAXN + 1);
    int m = rand() % (MAXM + 1);
    printf("%d %d\n", n, m);

    while (n--) {
        int j = rand() % MAXI + 1;
        int i = rand() % j;
        printf("%d %d\n", i, j);
    }
    while (m--) {
        int j = rand() % MAXI + 1;
        int i = rand() % j;
        int r = rand() % MAXI + 1;
        printf("%d %d %d\n", i, j, r);
    }
}

int main()
{
    srand(time(NULL));

    int T = MAXT;

    while (T--) test_case();
    puts("0 0");

    return 0;
}

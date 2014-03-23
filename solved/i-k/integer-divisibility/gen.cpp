#include <cstdio>
#include <cstdlib>
#include <ctime>

#define MAXT 125
#define MAXN 1000000

void test_case()
{
    int n;

    do {
        n = rand() % MAXN + 1;
    } while (n % 2 == 0 || n % 5 == 0);

    int d = rand() % 9 + 1;

    printf("%d %d\n", n, d);
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    while (T--) test_case();

    return 0;
}

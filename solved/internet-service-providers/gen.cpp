#include <cstdio>
#include <cstdlib>
#include <ctime>

#define MAXT 100
#define MAXC 1000000000
#define MAXN 1000000000

void test_case()
{
    int N = rand() % (MAXN + 1);
    int C = rand() % (MAXC + 1);

    printf("%d %d\n", N, C);
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    while (T--) test_case();

    return 0;
}

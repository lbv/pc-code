#include <cstdio>
#include <cstdlib>
#include <ctime>


#define MAXT 100
#define MAXN 20000000


void test_case()
{
    int N = rand() % (MAXN + 1);

    if (rand() % 15 == 0) N = rand() % 1000;

    int M = rand() % (N + 1);
    printf("%d %d\n", N, M);
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    while (T--) test_case();

    return 0;
}

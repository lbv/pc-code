#include <cstdio>
#include <cstdlib>
#include <ctime>


#define MAXT 65
#define MAXN 1000000000


void test_case()
{
    int N = rand() % MAXN + 1;

    if (rand() % 8 == 0) N = rand() % 100 + 1;
    printf("%d\n", N);
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    while (T--) test_case();

    return 0;
}

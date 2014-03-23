#include <cstdio>
#include <cstdlib>
#include <ctime>


#define MAXT 100000
#define MAXB 5000000


void test_case()
{
    int b = rand() % (MAXB - 1) + 2;

    if (rand() % 25 == 0) b = rand() % 1000 + 2;

    int a = rand() % (b - 1) + 2;

    if (b > 1000 && rand() % 25 == 0) a = rand() % 1000 + 2;

    printf("%d %d\n", a, b);
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    while (T--) test_case();

    return 0;
}

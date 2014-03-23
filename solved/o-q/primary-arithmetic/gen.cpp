#include <cstdio>
#include <cstdlib>
#include <ctime>


#define MAXT 100
#define MAXN 999999999


void test_case()
{
    int a = rand() % (MAXN + 1);
    int b = rand() % (MAXN + 1);

    if (rand() % 10 == 0) a = rand() % 1000;
    if (rand() % 10 == 0) b = rand() % 1000;

    printf("%d %d\n", a, b);
}

int main()
{
    srand(time(NULL));

    int T = MAXT;

    while (T--) test_case();
    puts("0 0");

    return 0;
}

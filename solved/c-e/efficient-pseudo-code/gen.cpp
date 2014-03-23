#include <cstdio>
#include <cstdlib>
#include <ctime>

#define MAXT 5000

void test_case()
{
    int n = rand();
    int m = rand();

    if (rand() % 8 == 0) n = rand() % 1000;
    if (rand() % 8 == 0) m = rand() % 1000;

    if (n == 0) ++n;

    printf("%d %d\n", n, m);
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    while (T--) test_case();

    return 0;
}

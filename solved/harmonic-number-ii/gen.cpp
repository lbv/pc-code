#include <cstdio>
#include <cstdlib>
#include <ctime>

#define MAXT 1000

void test_case()
{
    int n = rand();

    if (n == 0) ++n;

    printf("%d\n", n);
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    while (T--) test_case();

    return 0;
}

#include <cstdio>
#include <cstdlib>
#include <ctime>

#define MAXT 1000
#define MAXN 10000

void test_case()
{
    for (int i = 0; i < 6; ++i)
        printf("%d ", rand());
    int n = rand() % (MAXN + 1);
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

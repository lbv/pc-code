#include <cstdio>
#include <cstdlib>
#include <ctime>


#define MAXT 20000
#define MAXN 1000000000
#define PRED 1


void test_case()
{
    int n = rand() % (MAXN + 1);

    if (rand() % 10 == 0)
        n = rand() % 1000;

    printf("%d\n", n);
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

#if PRED
    for (int i = 0; i <= 100; ++i) {
        printf("%d\n%d\n", i, MAXN - i);
        T -= 2;
    }
#endif

    while (T--) test_case();

    return 0;
}

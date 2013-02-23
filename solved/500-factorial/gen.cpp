#include <cstdio>
#include <cstdlib>
#include <ctime>


#define MAXT 100
#define MAXN 1000
#define PRE  1


void test_case()
{
    int n = rand() % (MAXN + 1);
    printf("%d\n", n);
}

int main()
{
    srand(time(NULL));

    int T = MAXT;

#if PRE
    for (int i = 0; i < 5; ++i) {
        printf("%d\n%d\n", i, MAXN - i);
        T -= 2;
    }
#endif

    while (T--) test_case();

    return 0;
}

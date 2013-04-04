#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 100
#define MAXN 100000000
#define MAXA 10000
#endif

#if 1
#define MAXT 100
#define MAXN 1000
#define MAXA 500
#endif


void test_case()
{
    int n = rand() % (MAXN + 1);
    int a = rand() % MAXA + 1;
    int b = rand() % MAXA + 1;
    int c = rand() % MAXA + 1;
    printf("%d %d %d %d\n", n, a, b, c);
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    while (T--) test_case();

    return 0;
}

#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 100
#define MAXN 100
#define MAXW 100000
#endif

#if 1
#define MAXT 20
#define MAXN 50
#define MAXW 10000
#endif


void test_case(bool crit = false)
{
    int n = crit ? MAXN : rand() % (MAXN - 1) + 2;
    printf("\n%d\n", n);

    int leftw = MAXW;

    while (n--) {
        int maxw = leftw / (n + 1);
        int w = rand() % maxw + 1;
        printf("%d\n", w);
        leftw -= w;
    }
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    test_case(true); --T;
    while (T--) test_case();

    return 0;
}

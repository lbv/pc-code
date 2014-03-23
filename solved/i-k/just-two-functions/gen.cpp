#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 50
#define MAXCOEF 24999
#define MAXBASE 24999
#define MAXMOD  24999
#define MAXQ    100
#endif

#if 1
#define MAXT 20
#define MAXCOEF 100
#define MAXBASE 100
#define MAXMOD  80
#define MAXQ    12
#endif


void test_case(bool crit = false)
{
    puts("");

    for (int i = 0; i < 3; ++i)
        printf("%s%d", i > 0 ? " " : "", rand() % (MAXCOEF + 1));
    puts("");
    for (int i = 0; i < 3; ++i)
        printf("%s%d", i > 0 ? " " : "", rand() % (MAXCOEF + 1));
    puts("");

    for (int i = 0; i < 3; ++i)
        printf("%s%d", i > 0 ? " " : "", rand() % (MAXBASE + 1));
    puts("");
    for (int i = 0; i < 3; ++i)
        printf("%s%d", i > 0 ? " " : "", rand() % (MAXBASE + 1));
    puts("");

    int M = rand() % MAXMOD + 1;
    int q = crit ? MAXQ : rand() % MAXQ + 1;
    printf("%d\n%d\n", M, q);

    for (int i = 0; i < q; ++i) {
        if (i > 0) putchar(' ');
        int n = rand();
        if (rand() % 15 == 0) n = rand() % 1000;
        printf("%d", n);
    }
    puts("");
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

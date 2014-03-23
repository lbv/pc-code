#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 100
#define MAXR 100
#define MAXH 100
#endif

#if 1
#define MAXT 15
#define MAXR 100
#define MAXH 100
#endif


void test_case()
{
    int r1 = rand() % (MAXR - 1) + 2;
    int r2 = rand() % (r1 - 1) + 1;

    int h = rand() % MAXH + 1;
    int p = rand() % h + 1;

    printf("%d %d %d %d\n", r1, r2, h, p);
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    while (T--) test_case();

    return 0;
}

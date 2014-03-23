#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 12000
#define MAXQ 20
#define MAXK 50
#endif

#if 1
#define MAXT 12000
#define MAXQ 10
#define MAXK 15
#endif


void test_case()
{
    int q = rand() % (MAXQ - 1) + 2;
    int p = rand() % (q - 1) + 1;

    int k1, k2;
    do {
        k1 = rand() % MAXK + 1;
        k2 = rand() % MAXK + 1;
    } while(k1 + k2 > MAXK);

    printf("%d %d %d %d\n", p, q, k1, k2);
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    while (T--) test_case();

    return 0;
}

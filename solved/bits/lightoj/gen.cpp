#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 10000
const unsigned int MAXI = (1U << 31) - 1 ;
#define USE_PRE 1
#endif

#if 1
#define MAXT 100
const unsigned int MAXI = 1000;
#define USE_PRE 0
#endif


void test_case()
{
    int N = rand() % MAXI;

    if (rand() % 10 == 0) N = rand() % 1000;
    printf("%d\n", N);
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

#if USE_PRE
    for (int i = 0; i < 15; ++i) {
        printf("%d\n%u\n", i, MAXI - i);
        T -= 2;
    }
#endif

    while (T--) test_case();

    return 0;
}

#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 1
#define MAXT 200
#define MAXB 2000000000
#define MAXK 9999
#endif

#if 0
#define MAXT 50
#define MAXB 1000000
#define MAXK 100
#endif


void test_case()
{
    int B = rand() % MAXB + 1;
    if (rand() % 10 == 0) B = rand() % 10000 + 1;

    int A = rand() % B + 1;
    int K = rand() % MAXK + 1;

    printf("%d %d %d\n", A, B, K);
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    while (T--) test_case();

    return 0;
}

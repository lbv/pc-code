#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 1
#define MAXT 200
#define MAXN 1000
#define MAXK 300
#define MAXM 10000
#endif

#if 0
#define MAXT 500
#define MAXN 100
#define MAXK 80
#define MAXM 100
#endif


void test_case()
{
    int N = rand() % MAXN + 1;
    int Lim = N < 300 ? N : 300;
    int K = rand() % Lim + 1;

    printf("%d %d\n", N, K);
    for (int i = 0; i <= N; ++i)
        printf("%d\n", rand() % MAXM + 1);
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    while (T--) test_case();

    return 0;
}

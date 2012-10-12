#include <cstdio>
#include <cstdlib>
#include <ctime>

/*
#define MAXT 200
#define MAXN 1000
#define MAXK 300
#define MAXM 10000
*/

#define MAXT 20
#define MAXN 15
#define MAXK 12
#define MAXM 100



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

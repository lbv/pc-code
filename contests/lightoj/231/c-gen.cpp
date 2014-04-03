#include <cstdio>
#include <cstdlib>
#include <ctime>


#define MAXT 200
#define MAXN 11
#define MAXM 11

const int MinS = -100;
const int MaxS = 100;
const int SRange = MaxS - MinS + 1;


void test_case()
{
    int N = rand() % (MAXN - 1) + 2;
    int M = rand() % (MAXM - 1) + 2;
    int K = rand() % (N - 1) + 2;

    printf("\n%d %d %d\n", N, M, K);

    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            int S = rand() % SRange + MinS;
            if (rand() % 4 == 0)
                S = 0;

            printf("%s%d", j == 0 ? "" : " ", S);
        }
        putchar('\n');
    }
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    while (T--) test_case();

    return 0;
}

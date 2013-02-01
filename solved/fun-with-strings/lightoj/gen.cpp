#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;


#if 0
#define MAXT 300
#define MOD  1000000007
#define PRE  1
#endif

#if 1
#define MAXT 100
#define MOD  1000000007
#define PRE  0
#endif


typedef long long i64;

typedef vector<i64> IV;

void test_case()
{
    int N, X, M, Y, K;

    do {
        N = rand() % 100 + 1;
        M = rand() % 100 + 1;
    } while(N == M);

    X = rand() % 100 + 1;
    Y = rand() % 100 + 1;
    K = rand() % 100 + 1;

    if (rand() % 5 == 0) {
        IV f, g;
        f.push_back(rand() % 10);
        g.push_back(rand() % 10);

        while (true) {
            i64 fp = g.back();
            i64 gp = g.back() + f.back();

            if (gp > MOD || fp + gp > MOD) break;
            f.push_back(fp);
            g.push_back(gp);
        }

        int n = f.size();
        do {
            N = rand() % n + 1;
            M = rand() % n + 1;
        } while (N == M);
        X = f[N - 1] + g[N - 1];
        Y = f[M - 1] + g[M - 1];
        K = rand() % n + 1;
    }

    printf("%d %d %d %d %d\n", N, X, M, Y, K);
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

#if PRE
    for (int i = 1; i <= 3; ++i)
        for (int j = 1; j <= 3; ++j)
            for (int k = i + 1; k <= 3; ++k)
                for (int l = 1; l <= 3; ++l)
                    for (int m = 1; m <= 3; ++m) {
                        printf("%d %d %d %d %d\n", i, j, k, l, m);
                        --T;
                    }
#endif

    while (T--) test_case();

    return 0;
}

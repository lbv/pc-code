#include <cstdio>
#include <cstdlib>

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
    printf("%d %d %d %d %d\n", N, X, M, Y, K);
}

int main()
{
    int T = 300;
    printf("%d\n", T);

    for (int i = 1; i <= 3; ++i)
        for (int j = 1; j <= 3; ++j)
            for (int k = i + 1; k <= 3; ++k)
                for (int l = 1; l <= 3; ++l)
                    for (int m = 1; m <= 3; ++m) {
                        printf("%d %d %d %d %d\n", i, j, k, l, m);
                        --T;
                    }

    while (T--) test_case();

    return 0;
}

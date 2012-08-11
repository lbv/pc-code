#include <cstdio>
#include <cstdlib>
#include <ctime>

#define MAXT 200
#define MAXM 12
#define MAXN 12

void test_case()
{
    int M = rand() % (MAXM - 5) + 6;
    int N = rand() % (MAXN - 5) + 6;

    printf("%d %d\n", M, N);

    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            char c = '.';
            if (rand() % 2 != 0)
                c = '#';
            if (i == 0 || j == 0 || i == M - 1 || j == N - 1)
                if (rand() % 4 != 0)
                    c = '#';
            putchar(c);
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

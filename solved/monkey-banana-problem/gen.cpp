#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 50
#define MAXN 100
const int MAXI = (1 << 15) - 1;
#endif

#if 1
#define MAXT 20
#define MAXN 6
const int MAXI = 100;
#endif


void test_case(bool crit = false)
{
    int N = crit ? MAXN : rand() % MAXN + 2;
    printf("%d\n", N);

    for (int i = 1; i <= N; ++i) {
        for (int j = 0; j < i; ++j) {
            if (j > 0) putchar(' ');
            int n = rand() % MAXI + 1;
            printf("%d", n);
        }
        putchar('\n');
    }

    for (int i = 1; i < N; ++i) {
        for (int j = 0, J = N - i; j < J; ++j) {
            if (j > 0) putchar(' ');
            int n = rand() % MAXI + 1;
            printf("%d", n);
        }
        putchar('\n');
    }
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    test_case(true); --T;
    while (T--) test_case();

    return 0;
}

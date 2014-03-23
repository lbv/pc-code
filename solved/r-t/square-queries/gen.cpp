#include <cstdio>
#include <cstdlib>
#include <ctime>


#define MAXT 3
#define MAXN 500
#define MAXQ 50000
#define MAXI 100000


void test_case(bool crit = false)
{
    int N = crit ? MAXN : rand() % MAXN + 1;
    int Q = crit ? MAXQ : rand() % (MAXQ + 1);

    printf("\n%d %d\n", N, Q);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (j > 0) putchar(' ');
            printf("%d", rand() % (MAXI + 1));
        }
        puts("");
    }
    while (Q--) {
        int I = rand() % N + 1;
        int J = rand() % N + 1;
        int S;

        do {
            S = rand() % N + 1;
        } while (I + S - 1 > N || J + S - 1 > N);
        printf("%d %d %d\n", I, J, S);
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

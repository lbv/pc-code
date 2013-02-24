#include <cstdio>
#include <cstdlib>
#include <ctime>


#define MAXT 99
#define MAXM 99
#define MAXI 1000000000


void test_case(bool crit = false)
{
    int M = crit ? MAXM : rand() % (MAXM - 1) + 2;

    for (int i = 0; i < M; ++i) {
        if (i > 0) putchar(' ');
        int n = rand() % MAXI + 1;

        if (rand() % 20 == 0) n = rand() % 1000 + 1;
        printf("%d", n);
    }
    puts("");
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

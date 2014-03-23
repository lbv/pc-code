#include <cstdio>
#include <cstdlib>
#include <ctime>

#define MAXT 50
#define MAXN 100000
//#define MAXN 100
#define MAXH 1000000000

void test_case(bool crit = false)
{
    int N = rand() % MAXN + 1;

    if (rand() % 5 == 0) 
        N = 1 << (rand() % 10);

    int MAXC = N < 30 ? N : 30;
    int C = rand() % MAXC + 1;

    if (crit) N = MAXN, C = 30;

    printf("%d %d\n", N, C);

    for (int i = 0; i < N; ++i) {
        if (i > 0) putchar(' ');
        int h = rand() % MAXN + 1;
        if (crit) h = i + 1;
        printf("%d", h);
    }
    putchar('\n');

    for (int i = 0; i < N; ++i) {
        if (i > 0) putchar(' ');
        int c = rand() % C;
        if (i < C) c = i;
        printf("%d", c);
    }
    putchar('\n');
}

int main()
{
    srand(time(NULL));

    int T = MAXT;

    test_case(true); --T;
    while (T--) test_case();
    puts("0 0");

    return 0;
}

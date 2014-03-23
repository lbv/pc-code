#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 50
#define MAXN 99
#endif

#if 1
#define MAXT 20
#define MAXN 50
#endif


void test_case(bool crit=false)
{
    int N = rand() % MAXN + 1;
    if (crit) N = MAXN;
    printf("%d\n", N);

    int p = rand() % 4 + 2;
    while (N--) {
        char c = rand() % p == 0 ? '#' : '.';
        putchar(c);
    }
    putchar('\n');
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

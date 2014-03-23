#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 100
#define MAXL 1000
#endif

#if 1
#define MAXT 20
#define MAXL 30
#endif


void test_case(bool crit = false)
{
    int len = crit ? MAXL : rand() % MAXL + 1;
    int alpha = crit ? 26 : rand() % 26 + 1;

    for (int i = 0; i < len; ++i) {
        int c = 'a' + rand() % alpha;
        printf("%c", c);
    }
    putchar('\n');
}

int main()
{
    srand(time(NULL));

    int T = MAXT;

    test_case(true); --T;
    while (T--) test_case();

    return 0;
}

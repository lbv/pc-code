#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 1
#define MAXT   50
#define MAXLEN 100000
#endif

#if 0
#define MAXT   20
#define MAXLEN 20
#endif


void test_case(bool crit = false)
{
    int len = crit ? MAXLEN : rand() % (MAXLEN + 1);

    for (int i = 0; i < len; ++i) {
        int p = rand() % 15;

        char c;
        if      (p < 5) c = 'a' + rand() % 26;
        else if (p < 10) c = 'A' + rand() % 26;
        else if (p < 13) c = rand() % 2 == 0 ? ' ' : '\t';
        else            c = rand() % (127 - 31) + 32;

        putchar(c);
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

#include <cstdio>
#include <cstdlib>
#include <ctime>


#define MAXT 100
#define MAXLEN 100


void test_case(bool crit = false)
{
    int len1 = crit ? MAXLEN : rand() % MAXLEN + 1;
    int len2 = crit ? MAXLEN : rand() % MAXLEN + 1;

    putchar('\n');
    for (int i = 0; i < len1; ++i)
        printf("%c", 'a' + (rand() % 26));
    putchar('\n');
    for (int i = 0; i < len2; ++i)
        printf("%c", 'a' + (rand() % 26));
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

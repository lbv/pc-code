#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 1
#define MAXT 35
#define MAXN 15
#define MAXLEN 100
#endif

#if 0
#define MAXT 25
#define MAXN 5
#define MAXLEN 6
#endif


char str[MAXLEN + 1];

const char alpha[] = "ACGT";
const int nalpha = 4;


void test_case(bool crit = false)
{
    int n = rand() % MAXN + 1;
    if (crit) n = MAXN;
    printf("%d\n", n);

    while (n--) {
        int len = rand() % MAXLEN + 1;
        if (crit) len = MAXLEN;

        for (int i = 0; i < len; ++i)
            str[i] = alpha[rand() % nalpha];
        str[len] = 0;

        printf("%s\n", str);
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

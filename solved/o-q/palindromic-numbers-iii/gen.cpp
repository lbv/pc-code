#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 1
#define MAXT 30
#define MAXLEN 100000
#endif

#if 0
#define MAXT 300
#define MAXLEN 10
#endif


char num[MAXLEN + 1];


void gen1(bool crit = false)
{
    int len = crit ? MAXLEN : rand() % MAXLEN + 1;

    int d = rand() % 9 + 1;
    printf("%d", d);
    --len;

    while (len--) {
        d = rand() % 10;
        printf("%d", d);
    }
    putchar('\n');
}

void gen2(bool crit = false)
{
    int len = crit ? MAXLEN : rand() % MAXLEN + 1;

    int h = (len + 1) / 2;
    for (int i = 0; i < h; ++i) num[i] = '0' + rand() % 10;
    num[0] = '1' + rand() % 9;
    num[len] = 0;

    for (int i = 0, j = len - 1; i < j; ++i, --j)
        num[j] = num[i];

    printf("%s\n", num);
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    gen1(true); --T;
    gen2(true); --T;
    while (T--) {
        int n = rand() % 10;
        if (n < 3) gen1();
        else gen2();
    }

    return 0;
}

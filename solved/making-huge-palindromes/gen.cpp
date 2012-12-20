#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 1
#define MAXT   10
#define MAXLEN 1000000
#endif

#if 0
#define MAXT   50
#define MAXLEN 100
#endif


char S[MAXLEN + 1];


void test_case(bool crit=false)
{
    int len = crit ? MAXLEN : rand() % MAXLEN + 1;
    len = MAXLEN - (rand() % 20);

    int range = rand() % 26 + 1;

    for (int i = 0; i <= len; ++i)
        S[i] = 'a' + (rand() % range);

    if (rand() % 5 != 0) {
        int n = rand() % len;
        if (rand() % 3 == 0) n = len / 2;
        for (int i = n, j = n; i < len && j >= 0; ++i, --j)
            S[i] = S[j];
    }

    S[len] = 0;
    printf("%s\n", S);
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

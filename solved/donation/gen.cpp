#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 100
#define MAXN 50
#define MAXLEN 100
#endif

#if 1
#define MAXT 25
#define MAXN 8
#define MAXLEN 50
#endif


void test_case()
{
    int n = rand() % (MAXN - 1) + 2;

    printf("\n%d\n", n);

    int tot = n*n;
    int zp  = tot / 10;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j > 0) putchar(' ');

            int len = rand() % (MAXLEN + 1);
            if (rand() % tot <= zp) len = 0;

            printf("%d", len);
        }
        putchar('\n');
    }
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    while (T--) test_case();

    return 0;
}

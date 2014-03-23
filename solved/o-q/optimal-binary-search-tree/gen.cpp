#include <cstdio>
#include <cstdlib>
#include <ctime>

#define MAXT 100
#define MAXN 250
#define MAXF 100

void test_case()
{
    int n = rand() % MAXN + 1;

    printf("%d", n);

    while(n--) {
        int f = rand() % (MAXF + 1);
        printf(" %d", f);
    }
    putchar('\n');
}

int main()
{
    srand(time(NULL));

    int T = MAXT;

    while (T--) test_case();

    return 0;
}

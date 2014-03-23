#include <cstdio>
#include <cstdlib>
#include <ctime>

#define MAXT  100
#define MAXN  30
#define MAXW  2000000000
#define MAXW2 1000000000

void test_case()
{
    int n = rand() % MAXN + 1;
    int W = rand() % MAXW + 1;

    printf("%d %d\n", n, W);

    for (int i = 0; i < n; ++i) {
        printf("%s%d", i == 0 ? "" : " ", rand() % MAXW2);
    }
    putchar('\n');
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    printf("30 2000000000\n");
    for (int i = 0; i < 30; ++i)
        printf("%s%d", i == 0 ? "" : " ", 1);
    puts("");
    --T;

    while (T--) test_case();

    return 0;
}

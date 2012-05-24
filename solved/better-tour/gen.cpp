#include <cstdio>
#include <cstdlib>
#include <ctime>

#define MAXN 50000
void test_case()
{
    int n = rand() % (MAXN - 1) + 2;
    printf("%d\n", n);

    for (int i = 0; i < n; ++i) {
        int v = rand() % MAXN + 1;

        printf("%s%d", i == 0 ? "" : " ", v);
    }
    putchar('\n');
}

int main()
{
    srand(time(NULL));

    int T = 5;
    printf("%d\n", T);

    while (T--)
        test_case();

    return 0;
}

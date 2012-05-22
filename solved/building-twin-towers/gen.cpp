#include <cstdio>
#include <cstdlib>
#include <ctime>

void test_case()
{
    int n = rand() % 50 + 1;

    printf("%d\n", n);

    while (n--) {
        int h = rand() % 10000 + 1;

        printf("%d%s", h, n == 0 ? "" : " ");
    }
    putchar('\n');
}

int main()
{
    srand(time(NULL));

    int T = 10;
    printf("%d\n", T);

    while (T--)
        test_case();

    return 0;
}

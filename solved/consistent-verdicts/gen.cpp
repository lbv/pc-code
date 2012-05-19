#include <cstdio>
#include <cstdlib>
#include <ctime>

void test_case()
{
    int N = rand() % 700 + 1;
    printf ("%d\n", N);

    while (N--) {
        int x = rand() % 30001;
        int y = rand() % 30001;

        printf("%d %d\n", x, y);
    }
}

int main()
{
    srand(time(NULL));

    int T = 100;
    printf("%d\n", T);

    while (T--)
        test_case();

    return 0;
}

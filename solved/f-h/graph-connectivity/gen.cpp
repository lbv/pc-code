#include <cstdio>
#include <cstdlib>
#include <ctime>


#define MAXT 100


void test_case()
{
    int n = rand() % (26 - 1) + 2;

    printf("\n%c\n", 'A' + n - 1);
    int m = rand() % (n * n);

    while (m--) {
        int u, v;
        do {
            u = rand() % n + 1;
            v = rand() % n + 1;
        } while (u == v);

        printf("%c%c\n", 'A' + u - 1, 'A' + v - 1);
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

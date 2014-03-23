#include <cstdio>
#include <cstdlib>
#include <ctime>


#define MAXT 100
#define MAXN 15


void test_case()
{
    int n;
    do {
        n = rand() % (MAXN - 2) + 3;
    } while (n % 2 == 0);
    printf("%d\n", n);
}

int main()
{
    srand(time(NULL));

    int T = MAXT;

    for (int i = 3; i <= MAXN; i += 2) {
        printf("%d\n", i);
        T += 2;
    }

    while (T--) test_case();

    return 0;
}

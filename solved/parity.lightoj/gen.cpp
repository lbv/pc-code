#include <cstdio>
#include <cstdlib>
#include <ctime>


#define MAXT 1000
#define MAXN 2147483647


typedef unsigned int u32;


void test_case()
{
    u32 n;

    do {
        n = rand();
    } while (n < 1 || n > MAXN);

    if (rand() % 20 == 0)
        n = rand() % 1000 + 1;

    printf("%u\n", n);
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    for (int i = 0; i < 31; ++i) {
        printf("%u\n", 1 << i);
        --T;

        if (i > 0) {
            printf("%u\n", (1 << i) - 1);
            --T;
        }
    }

    for (int i = 0; i < 100; ++i) {
        printf("%u\n", MAXN - i);
        --T;
    }

    while (T--) test_case();

    return 0;
}

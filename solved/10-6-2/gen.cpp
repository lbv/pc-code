#include <cstdio>
#include <cstdlib>
#include <ctime>


#define MAXT 100
#define MAXL 1000


void test_case()
{
    int L = rand() % MAXL + 1;
    printf("%d\n", L);
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    for (int i = 0; i < 5; ++i) {
        printf("%d\n%d\n", i + 1, MAXL - i);
        T -= 2;
    }

    while (T--) test_case();

    return 0;
}

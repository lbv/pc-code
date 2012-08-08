#include <cstdio>
#include <cstdlib>
#include <ctime>

#define MAXT 10000

const unsigned int M = (1 << 30) - 1;

void test_case()
{
    int B = rand() % M + 1;
    int A = rand() % B + 1;

    printf("%d %d\n", A, B);
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    for (int B = 1; B <= 31; ++B)
        for (int A = 1; A <= B; ++A) {
            printf("%d %d\n", A, B);
            --T;
        }

    while (T--) test_case();

    return 0;
}

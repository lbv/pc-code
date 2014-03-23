#include <cstdio>
#include <cstdlib>
#include <ctime>

#define MAXT 1000
#define MAXA 100000

void test_case()
{
    for (int i = 0; i < 3; ++i) {
        int ia = rand() % MAXA + 1;
        double a = ia;
        a /= 100.0;
        printf("%s%.2lf", i != 0 ? " " : "", a);
    }
    putchar('\n');
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    while (T--) test_case();

    return 0;
}

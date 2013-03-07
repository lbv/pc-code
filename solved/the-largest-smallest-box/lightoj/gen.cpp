#include <cstdio>
#include <cstdlib>
#include <ctime>


#define MAXT 10000
#define MAXL 100
#define MAXD 4


void gen_number()
{
    int dig = rand() % (MAXD + 1);
    int p = 1;
    for (int i = 0; i < dig; ++i) p *= 10;
    int maxn = MAXL * p;

    int n = rand() % (maxn - 1) + 1;
    if (p == 1)
        printf("%d", n);
    else
        printf("%d.%d", n / p, n % p);
}

void test_case()
{
    gen_number();
    putchar(' ');
    gen_number();
    puts("");
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    while (T--) test_case();

    return 0;
}

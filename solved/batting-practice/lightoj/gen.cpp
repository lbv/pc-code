#include <cstdio>
#include <cstdlib>
#include <ctime>


#define MAXT 15000
#define MAXK 50


void test_case()
{
    double p = rand() % 1001;
    p /= 1000;

    int k1, k2;
    do {
        k1 = rand() % MAXK + 1;
        k2 = rand() % MAXK + 1;
    } while(k1 + k2 > MAXK);

    printf("%.3lf %d %d\n", p, k1, k2);
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    for (int i = 1; i < MAXK; ++i) {
        printf("0.5 %d %d\n", i, MAXK - i);
        printf("0.5 %d %d\n", MAXK - i, i);
        printf("0.33 %d %d\n", i, MAXK - i);
        printf("0.33 %d %d\n", MAXK - i, i);
        printf("0.0 %d %d\n", i, MAXK - i);
        printf("0.0 %d %d\n", MAXK - i, i);
        T -= 6;
    }
    while (T--) test_case();

    return 0;
}

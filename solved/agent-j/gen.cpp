#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 1000
#define MAXR 10000
#endif

#if 1
#define MAXT 20
#define MAXR 10000
#endif


double rand_r()
{
    int ir = rand() % MAXR + 1;
    double r = ir;
    r /= 100;
    return r;
}

void test_case()
{
    printf("%.2lf %.2lf %.2lf\n", rand_r(), rand_r(), rand_r());
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    while (T--) test_case();

    return 0;
}

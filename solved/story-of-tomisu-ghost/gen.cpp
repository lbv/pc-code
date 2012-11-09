#include <cstdio>
#include <cstdlib>
#include <ctime>


#define MAXCASES 4000
#define MAXN 100000
#define MAXT 1000


void test_case()
{
    int n = rand() % (MAXN - 1) + 2;
    int t = rand() % MAXT + 1;

    printf("%d %d\n", n, t);
}

int main()
{
    srand(time(NULL));

    int T = MAXCASES;
    printf("%d\n", T);

    while (T--) test_case();

    return 0;
}

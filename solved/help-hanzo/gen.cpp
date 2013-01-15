#include <cstdio>
#include <cstdlib>
#include <ctime>


#define MAXT 200
#define MAXDIFF 100000
const int MAXB = 1 << 30;


void test_case()
{
    int b = rand() % (MAXB - MAXDIFF) + MAXDIFF + 1;

    if (rand() % 6 == 0) b = MAXDIFF + (rand() % 1000) + 1;
    int a = b - (rand() % MAXDIFF);

    printf("%d %d\n", a, b);
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    while (T--) test_case();

    return 0;
}

#include <cstdio>
#include <cstdlib>
#include <ctime>


#define MAXT 100
/*
#define MAXN 20
#define MAXCOST 1000
*/
#define MAXN 8
#define MAXCOST 25


void test_case()
{
    int n = rand() % MAXN + 1;

    printf("\n%d\n", n);
    while (n--) {
        int R = rand() % MAXCOST + 1;
        int G = rand() % MAXCOST + 1;
        int B = rand() % MAXCOST + 1;
        printf("%d %d %d\n", R, G, B);
    }
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    while (T--) test_case();

    return 0;
}

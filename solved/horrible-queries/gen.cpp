#include <cstdio>
#include <cstdlib>
#include <ctime>


#define MAXT 5

#define MAXN 100000
#define MAXQ 50000
#define MAXV 1000


/*
#define MAXN 15
#define MAXQ 10
#define MAXV 50
*/


void test_case()
{
    int n = rand() % MAXN + 1;
    int q = rand() % MAXQ + 1;

    printf("%d %d\n", n, q);
    while (q--) {
        int com = rand() % 2;

        if (com == 0) {
            int y = rand() % n;
            int x = rand() % (y + 1);
            int v = rand() % MAXV + 1;
            printf("%d %d %d %d\n", com, x, y, v);
        }
        else {
            int y = rand() % n;
            int x = rand() % (y + 1);
            printf("%d %d %d\n", com, x, y);
        }
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

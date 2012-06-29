#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;

#define MAXCASES 10

#define MAXN 10000
#define MAXM 100000
#define MAXT 600

void test_case()
{
    int n = rand() % (MAXN - 1) + 2;
    int h = rand() % (min(n, 100) + 1);

    printf("%d\n%d", n, h);
    while (h--) {
        int c = rand() % n + 1;
        printf(" %d", c);
    }

    int m = rand() % MAXM + 1;
    printf("\n%d\n", m);

    while (m--) {
        int u, v;
        do {
            u = rand() % n + 1;
            v = rand() % n + 1;
        } while (u == v);

        int t = rand() % MAXT + 1;

        printf("%d %d %d\n", u, v, t);
    }
}

int main()
{
    srand(time(NULL));

    int T = MAXCASES;

    while (T--) test_case();
    puts("0");

    return 0;
}

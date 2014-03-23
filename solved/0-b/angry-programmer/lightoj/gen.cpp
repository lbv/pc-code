#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
using namespace std;


#define MAXT 500
#define MAXM 50
#define MAXW 1200
#define MAXC 100000

#define Zero(v) memset((v), 0, sizeof(v))


bool vis[MAXM][MAXM];


void test_case(bool crit = false)
{
    int M = crit ? MAXM : rand() % (MAXM - 1) + 2;
    int MaxW = min(MAXW, M*(M-1) / 2);
    int W = crit ? MAXW : rand() % (MaxW + 1);

    printf("%d %d\n", M, W);
    for (int i = 2; i < M; ++i) {
        if (i > 2) putchar(' ');
        int c = rand() % (MAXC + 1);
        printf("%d", c);
    }
    puts("");

    Zero(vis);
    while (W--) {
        int i, j;
        do {
            i = rand() % M;
            j = rand() % M;
        } while (i == j || vis[i][j]);

        vis[i][j] = vis[j][i] = true;
        int c = rand() % (MAXC + 1);
        printf("%d %d %d\n", i + 1, j + 1, c);
    }
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    test_case(true); --T;
    while (T--) test_case();

    return 0;
}

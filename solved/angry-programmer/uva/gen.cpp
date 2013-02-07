#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
using namespace std;


#if 1
#define MAXT 100
#define MAXM 50
#define MAXW 1000
#define MAXC 100000
#define NL   0
#endif

#if 0
#define MAXT 20
#define MAXM 10
#define MAXW 40
#define MAXC 100
#define NL   1
#endif


#define Zero(v) memset((v), 0, sizeof(v))


bool vis[MAXM][MAXM];


void test_case(bool crit = false)
{
    int M = crit ? MAXM : rand() % (MAXM - 1) + 2;
    int MaxW = min(MAXW, M*(M-1) / 2);
    int W = crit ? MAXW : rand() % (MaxW + 1);

#if NL
    puts("\n");
#endif

    printf("%d %d\n", M, W);
    for (int i = 2; i < M; ++i) {
        int c = rand() % (MAXC + 1);
        printf("%d %d\n", i, c);
    }

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

    test_case(true); --T;
    while (T--) test_case();

    puts("0 0");

    return 0;
}

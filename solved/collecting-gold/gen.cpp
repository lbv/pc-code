#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;


#if 0
#define MAXT 100
#define MAXM 20
#define MAXN 20
#define MAXG 15
#endif

#if 1
#define MAXT 20
#define MAXM 8
#define MAXN 8
#define MAXG 6
#endif


char grid[MAXM][MAXN + 1];


void test_case()
{
    int m = rand() % MAXM + 1;
    int n = rand() % MAXN + 1;
    printf("\n%d %d\n", m, n);

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j)
            grid[i][j] = '.';
        grid[i][n] = 0;
    }

    int r, c;
    r = rand() % m;
    c = rand() % n;
    grid[r][c] = 'x';

    int max_gold = min(MAXG, m*n - 1);

    int gold = rand() % (max_gold + 1);

    while (gold--) {
        do {
            r = rand() % m;
            c = rand() % n;
        } while (grid[r][c] != '.');

        grid[r][c] = 'g';
    }

    for (int i = 0; i < m; ++i)
        puts(grid[i]);
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    while (T--) test_case();

    return 0;
}

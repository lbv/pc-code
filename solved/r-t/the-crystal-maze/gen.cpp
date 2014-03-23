#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 10
#define MAXM 500
#define MAXN 500
#define MAXQ 1000
#define NL   0
#endif

#if 1
#define MAXT 20
#define MAXM 8
#define MAXN 8
#define MAXQ 8
#define NL   1
#endif


char maze[MAXM][MAXN + 1];
int  free_cells[MAXM * MAXN][2];
int  nfree;


void test_case(bool crit = false)
{
#if NL
    puts("");
#endif

    int M = crit ? MAXM : rand() % (MAXM - 1) + 2;
    int N = crit ? MAXN : rand() % (MAXN - 1) + 2;
    int Q = crit ? MAXQ : rand() % MAXQ + 1;
    printf("%d %d %d\n", M, N, Q);

    for (int i = 0; i < M; ++i) {
        maze[i][N] = 0;
        for (int j = 0; j < N; ++j)
            maze[i][j] = '.';
    }

    int walls, crystals;
    int cells = M*N;

    do {
        walls    = rand() % cells;
        crystals = rand() % cells;
    } while (walls + crystals > cells * 2 / 3);

    for (int i = 0; i < walls; ++i) {
        int r, c;
        do {
            r = rand() % M;
            c = rand() % N;
        } while (maze[r][c] != '.');
        maze[r][c] = '#';
    }
    for (int i = 0; i < crystals; ++i) {
        int r, c;
        do {
            r = rand() % M;
            c = rand() % N;
        } while (maze[r][c] != '.');
        maze[r][c] = 'C';
    }
    for (int i = 0; i < M; ++i)
        puts(maze[i]);

    nfree = 0;
    for (int i = 0; i < M; ++i)
        for (int j = 0; j < N; ++j)
            if (maze[i][j] == '.')
                free_cells[nfree][0] = i, free_cells[nfree++][1] = j;

    while (Q--) {
        int i = rand() % nfree;
        printf("%d %d\n", free_cells[i][0] + 1, free_cells[i][1] + 1);
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

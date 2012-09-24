#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;


#define MAXM 100
#define MAXN 8

#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); ++v)
#define Zero(v) memset((v), 0, sizeof(v))

// a bit that represents the cell at position (i,j) in a board of k columns
#define Cell(i,j,k) (1 << (i*k + j))


typedef unsigned long long u64;
typedef unsigned int       u32;

typedef vector<u32> UV;


int M, N;
char grid[MAXM][MAXM + 1];
char grid2[MAXM][MAXM + 1];

// cmb[i][b]: all possible combinations of tiles for a clear board of 2*i
// where the first row is described by the bitmask b
UV cmb[MAXN + 1][1 << MAXN];

// seg[i]: bitmask for rows i and i+1 of the board
u32 seg[MAXM];

u32 full_row;

u64 memo[MAXM][1 << MAXN];
bool memo_vis[MAXM][1 << MAXN];


void prepare()
{
    for (int k = 1; k <= MAXN; ++k) {
        UV g;  // group of combinations for k columns
        g.push_back(0);

        for (int j = 0; j < k; ++j) {
            UV aux;
            cFor (UV, s, g) {
                aux.push_back(*s);

                u32 blk;

                blk = Cell(0, j, k) | Cell(1, j, k);
                if ((*s & blk) == 0) aux.push_back(*s | blk);

                if (j + 1 < k) {
                    blk = Cell(0, j, k) | Cell(0, j + 1, k);
                    if ((*s & blk) == 0) aux.push_back(*s | blk);

                    blk = Cell(0, j, k) | Cell(1, j, k) |
                        Cell(1, j + 1, k);
                    if ((*s & blk) == 0) aux.push_back(*s | blk);

                    blk = Cell(0, j, k) | Cell(1, j, k) |
                        Cell(0, j + 1, k);
                    if ((*s & blk) == 0) aux.push_back(*s | blk);

                    blk = Cell(0, j + 1, k) | Cell(1, j, k) |
                        Cell(1, j + 1, k);
                    if ((*s & blk) == 0) aux.push_back(*s | blk);

                    blk = Cell(0, j, k) | Cell(0, j + 1, k) |
                        Cell(1, j + 1, k);
                    if ((*s & blk) == 0) aux.push_back(*s | blk);
                }
            }
            g = aux;
        }

        full_row = (1 << k) - 1;
        cFor (UV, b, g)
            cmb[k][*b & full_row].push_back(*b);
    }
}

void transpose()
{
    memcpy(grid2, grid, sizeof(grid));
    for (int i = 0; i < M; ++i)
        for (int j = 0; j < N; ++j)
            grid[j][i] = grid2[i][j];
    swap(M, N);
}

u64 f(int r, u32 b)
{
    if (r >= M) return 1;
    if (memo_vis[r][b]) return memo[r][b];

    u64 cnt = 0;
    u32 segp = seg[r] | b;

    UV &g = cmb[N][~(segp & full_row) & full_row];

    cFor (UV, s, g) {
        if ((segp & *s) != 0) continue;

        u32 result = segp | *s;

        if ((result & full_row) == full_row)
            cnt += f(r + 1, result >> N);
    }

    memo[r][b] = cnt;
    memo_vis[r][b] = true;
    return memo[r][b];
}

u64 solve()
{
    seg[0] = 0;
    for (int j = 0; j < N; ++j) {
        if (grid[0][j] == '#')
            seg[0] |= Cell(0, j, N);

        if (M < 2 || grid[1][j] == '#')
            seg[0] |= Cell(1, j, N);
    }

    for (int i = 1; i < M; ++i) {
        seg[i] = seg[i - 1] >> N;
        for (int j = 0; j < N; ++j)
            if (i + 1 >= M || grid[i + 1][j] == '#')
                seg[i] |= Cell(1, j, N);
    }

    full_row = (1 << N) - 1;
    Zero(memo_vis);
    return f(0, 0);
}

int main()
{
    prepare();

    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d", &M, &N);
        for (int i = 0; i < M; ++i) scanf("%s", grid[i]);

        if (N > MAXN) transpose();

        printf("Case %d: %llu\n", ++ncase, solve());
    }

    return 0;
}

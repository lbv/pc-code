#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

#define MAXM 20
#define MAXN 20
#define MAXGOLD 15
#define INF 6410

typedef unsigned int u32;

struct Pos {
    int r, c;
    Pos(int R, int C) : r(R), c(C) {}
    Pos() {}
};


// dp[i][b] has the minimum number of steps to visit all cells in the
// bitmask b, landing on the i'th gold cell last
int dp[MAXGOLD][1 << MAXGOLD];

// positions of all cells with gold
Pos gs[MAXGOLD];

int m, n;
char maze[MAXM][MAXN + 1];
int pos[1 << MAXGOLD];


int dist(const Pos &a, const Pos &b)
{
    return max(abs(a.r - b.r), abs(a.c - b.c));
}

u32 next_popcount(u32 n)
{
    u32 c = (n & -n);
    u32 r = n+c;
    return (((r ^ n) >> 2) / c) | r;
}
u32 init_popcount(int n) { return (1 << n) - 1; }
#define Back(b)    ((b) & -(b))
#define PopBack(b) (b &= ~Back(b))

int run_dp()
{
    Pos O;      // origin/ending point
    int G = 0;  // number of gold cells

    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j) {
            if (maze[i][j] == 'g')
                gs[G++] = Pos(i, j);
            else if (maze[i][j] == 'x')
                O = Pos(i, j);
        }

    if (G == 0) return 0;

    for (int i = 0; i < G; ++i)
        dp[i][1 << i] = dist(O, gs[i]);

    u32 top = 1 << G;

    for (int q = 2; q <= G; ++q) {
        for (u32 b = init_popcount(q); b < top; b = next_popcount(b)) {
            u32 it_b = b;

            while (it_b) {
                u32 to = Back(it_b);
                int i_to = pos[to];

                u32 from_b = b & ~to;
                int best = INF;

                for (u32 it_from = from_b; it_from; PopBack(it_from)) {
                    u32 from = Back(it_from);
                    int i_from = pos[from];

                    best = min(best, dp[i_from][from_b] +
                               dist(gs[i_from], gs[i_to]));
                }

                dp[i_to][b] = best;

                PopBack(it_b);
            }
        }
    }

    int ans = INF;
    for (int i = 0; i < G; ++i)
        ans = min(ans, dp[i][top - 1] + dist(gs[i], O));
    return ans;
}

void prepare()
{
    for (int i = 0; i < MAXGOLD; ++i)
        pos[1 << i] = i;
}

int main()
{
    prepare();

    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d", &m, &n);

        for (int i = 0; i < m; ++i) scanf("%s", maze[i]);

        printf("Case %d: %d\n", ++ncase, run_dp());
    }

    return 0;
}

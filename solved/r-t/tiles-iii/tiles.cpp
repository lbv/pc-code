#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;


#define MAXM 8
#define MAXN 100

#define Neg(v)  memset((v), -1, sizeof(v))
#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); ++v)

#define Cell(i,j) (1 << (j*M + i))


typedef unsigned int u32;


struct Blocks {
    u32 b;  // bitmask of a M*3 segment of the board
    int n;  // number of blocks that have been placed in it

    Blocks(u32 B, int N) : b(B), n(N) {}
};
typedef vector<Blocks> BV;


int M, N;
char grid[MAXM][MAXN + 1];

// seg[i]: bitmask of the board from column i to column i+2
u32 seg[MAXN];

int memo[MAXN][1 << (MAXM * 2)];
BV w;


// Returns the maximum number of blocks that can be placed on the board,
// starting on column c, after the first two columns have been modified
// according to bitmask b
int f(int c, u32 b)
{
    if (c >= N - 1) return 0;
    if (memo[c][b] >= 0) return memo[c][b];

    int best = 0;
    u32 s = seg[c] | b;

    cFor (BV, p, w) {
        if ((s & p->b) != 0) continue;

        u32 rs = s | p->b;
        int cur = p->n + f(c + 1, rs >> M);

        if (cur > best) best = cur;
    }

    return memo[c][b] = best;
}

int solve()
{
    // Calculate all possible ways to place blocks in a clear M*3 segment
    w = BV();
    w.push_back(Blocks(0, 0));

    for (int c = 0; c < 2; ++c)
        for (int r = 0; r < M; ++r) {
            u32 blk1 = 0;  // block of size 3*2
            if (r + 2 < M)
                for (int i = r; i <= r + 2; ++i)
                    for (int j = c; j <= c + 1; ++j)
                        blk1 |= Cell(i, j);

            u32 blk2 = 0;  // block of size 2*3
            if (r + 1 < M && c + 2 < 3)
                for (int i = r; i <= r + 1; ++i)
                    for (int j = c; j <= c + 2; ++j)
                        blk2 |= Cell(i, j);

            BV aux;
            cFor (BV, b, w) {
                aux.push_back(*b);

                if (blk1 != 0 && (b->b & blk1) == 0)
                    aux.push_back(Blocks(b->b | blk1, b->n + 1));
                if (blk2 != 0 && (b->b & blk2) == 0)
                    aux.push_back(Blocks(b->b | blk2, b->n + 1));
            }

            w = aux;
        }

    // Calculate the bitmasks of all M*3 segments of the board
    seg[0] = 0;
    for (int r = 0; r < M; ++r)
        for (int c = 0; c < 3; ++c)
            if (c >= N || grid[r][c] == '#')
                seg[0] |= Cell(r, c);

    for (int c = 1; c < N; ++c) {
        seg[c] = seg[c - 1] >> M;

        for (int r = 0; r < M; ++r)
            if (c + 2 >= N || grid[r][c + 2] == '#')
                seg[c] |= Cell(r, 2);
    }

    Neg(memo);
    return f(0, 0);
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d", &M, &N);
        for (int i = 0; i < M; ++i) scanf("%s", grid[i]);

        printf("Case %d: %d\n", ++ncase, solve());
    }

    return 0;
}

#include <cstdio>
#include <cstring>


#define MAXN 15

#define Zero(v) memset((v), 0, sizeof(v))
#define Neg(v)  memset((v), -1, sizeof(v))

#define GetFS(b) ((b) & -(b))
#define ClrFS(b) (b &= ~GetFS(b))
static const int m37pos[] = {
    32,  0,  1, 26,  2, 23, 27,  0,  3,
    16, 24, 30, 28, 11,  0, 13,  4,  7,
    17,  0, 25, 22, 31, 15, 29, 10, 12,
     6,  0, 21, 14,  9,  5, 20,  8, 19, 18
};
#define Ctz(x) (m37pos[(x) % 37])


typedef unsigned int u32;


int g[MAXN][MAXN];
int n, m;
u32 all;

double memo[MAXN][1 << MAXN];
bool   vis[MAXN][1 << MAXN];
bool   reach[MAXN][1 << MAXN];


void find_reachable()
{
    // reach[i][b] is true if all junctions in b are reachable from i
    for (u32 b = 0; b <= all; ++b)
        for (int i = 0; i < n; ++i) {
            if (b == 0) { reach[i][b] = true; continue; }

            bool ans = false;
            for (u32 r = b; r; ClrFS(r)) {
                u32 x = GetFS(r);
                int idx = Ctz(x);

                if (g[i][idx] >= 0) ans = reach[idx][b & ~x];

                if (ans) break;
            }

            reach[i][b] = ans;
        }
}

// the expected time to be caught when your location is u, and the unvisited
// junctions are represented by bitmask b
double f(int u, u32 b)
{
    if (vis[u][b]) return memo[u][b];

    int    k   = 0;  // number of valid neighbours
    double ans = 5.0;

    for (u32 r = b; r; ClrFS(r)) {
        u32 x = GetFS(r);
        int idx = Ctz(x);

        if (g[u][idx] >= 0 && reach[idx][b & ~x]) {
            ++k;
            ans += g[u][idx];
            ans += f(idx, b & ~x);
        }
    }

    ans = k == 0 ? 0.0 : ans / k;

    vis[u][b] = true;
    return memo[u][b] = ans;
}

double solve()
{
    find_reachable();

    Zero(vis);
    return f(0, all & ~1);
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d", &n, &m);

        all = (1 << n) - 1;
        Neg(g);

        while (m--) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            g[u][v] = g[v][u] = w;
        }

        printf("Case %d: %.8lf\n", ++ncase, solve());
    }

    return 0;
}

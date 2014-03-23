#include <cstdio>
#include <cstring>


#define MAXN 15
#define INF  (1 << 30)

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


int n, m;
int g[MAXN][MAXN];

// pv[i]: true if vertex i has an even degree
bool pv[MAXN];

int memo[1 << MAXN];


void floyd()
{
    for (int k = 0; k < n; k++)
        for(int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                if (g[i][k] == INF || g[k][j] == INF) continue;
                int t = g[i][k] + g[k][j];
                if (t < g[i][j]) g[i][j] = t;
            }
}

void init_graph()
{
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            g[i][j] = i == j ? 0 : INF;
}

// minimum cost of increasing the degree of vertices "b" by one
int f(u32 b)
{
    if (b == 0) return 0;
    if (memo[b] >= 0) return memo[b];

    int best = INF;

    int nv = 0;
    int vs[MAXN];

    for (u32 r = b; r; ClrFS(r)) {
        u32 x = GetFS(r);
        vs[nv++] = Ctz(x);
    }

    for (int i = 0; i < nv; ++i)
        for (int j = i + 1; j < nv; ++j) {
            u32 p = (1 << vs[i]) | (1 << vs[j]);
            int cur = g[vs[i]][vs[j]] + f(b & ~p);
            if (cur < best) best = cur;
        }

    return memo[b] = best;
}

int cost_euler_cycle()
{
    int odds = 0;
    u32 bmask = 0;

    for (int i = 0; i < n; ++i)
        if (! pv[i]) {
            ++odds;
            bmask |= 1 << i;
        }

    if (odds == 0) return 0;

    floyd();
    Neg(memo);
    return f(bmask);
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d", &n, &m);

        int ans = 0;
        init_graph();
        for (int i = 0; i < n; ++i) pv[i] = true;

        for (int i = 0; i < m; ++i) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            --u; --v;

            ans += w;
            if (w < g[u][v]) g[u][v] = g[v][u] = w;
            pv[u] = !pv[u];
            pv[v] = !pv[v];
        }

        ans += cost_euler_cycle();

        printf("Case %d: %d\n", ++ncase, ans);
    }

    return 0;
}

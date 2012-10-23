#include <cstdio>


#define MAXN 14

const int INF = 14 * 14 * 100000 + 10;

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


int n;
int C[MAXN][MAXN];

// dp[b]: the minimum cost for completing tasks in bitmask b
int dp[1 << MAXN];


int solve() {
    u32 all = (1 << n) - 1;

    for (u32 b = 1; b <= all; ++b) {
        int best = INF;

        for (u32 x = b; x; ClrFS(x)) {
            u32 lst = GetFS(x);
            int idx = Ctz(lst);

            u32 rest = b & ~lst;
            int curr = dp[rest] + C[idx][idx];

            for (u32 y = rest; y; ClrFS(y))
                curr += C[idx][Ctz(GetFS(y))];

            if (curr < best) best = curr;
        }

        dp[b] = best;
    }

    return dp[all];
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d", &n);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                scanf("%d", &C[i][j]);

        printf("Case %d: %d\n", ++ncase, solve());
    }

    return 0;
}

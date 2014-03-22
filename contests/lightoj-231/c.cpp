#include <cstdio>
#include <cstring>


#define MAXM 11
#define MAXN 11

const int IMPOS = (-100) * 11 + 10;

#define Zero(v) memset((v), 0, sizeof(v))
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


int S[MAXM][MAXN];
int N, M, K;

int memo[MAXM + 1][1 << MAXN];
bool vis[MAXM + 1][1 << MAXN];

int MaxPPS;  // max problems per setter


// next higher number with same number of 1's in binary
u32 next_popcount(u32 n)
{
    u32 c = (n & -n);
    u32 r = n+c;
    return (((r ^ n) >> 2) / c) | r;
}
// Returns first integer with exactly n bits set
u32 init_popcount(int n) { return (1 << n) - 1; }

// The maximum satisfaction after matching the first "s" setters
// with problems "p"
int dp(int s, u32 p)
{
    if (s == 0 && p == 0) return 0;
    if (vis[s][p]) return memo[s][p];
    vis[s][p] = true;

    int problems[MAXN];
    int np = 0;
    for (u32 b = p; b; ClrFS(b)) {
        u32 bit = GetFS(b);
        problems[np++] = Ctz(bit);
    }

    if (s > np) return memo[s][p] = IMPOS;
    if (s * MaxPPS < np) return memo[s][p] = IMPOS;

    int best = IMPOS;
    int i = s - 1;

    // match one setter with one problem
    for (int k = 0; k < np; ++k) {
        int j = problems[k];
        u32 bit_prob = 1 << j;

        if (S[i][j] != 0) {
            int rest = dp(s - 1, p & ~bit_prob);
            if (rest != IMPOS && S[i][j] + rest > best)
                best = S[i][j] + rest;
        }
    }

    if (MaxPPS > 1) {
        // match one setter with two problems
        for (int x = 0; x < np; ++x)
            for (int y = x + 1; y < np; ++y) {
                int j1 = problems[x];
                int j2 = problems[y];
                u32 b1 = 1 << j1;
                u32 b2 = 1 << j2;

                if (S[i][j1] != 0 && S[i][j2] != 0) {
                    int rest = dp(s - 1, p & ~b1 & ~b2);
                    int cur = S[i][j1] + S[i][j2] + rest;
                    if (rest != IMPOS && cur > best) best = cur;
                }
            }
    }

    return memo[s][p] = best;
}

int solve()
{
    int best = IMPOS;

    u32 top = 1 << N;
    Zero(vis);

    MaxPPS = K == 2 ? 1 : 2;

    for (u32 prob = init_popcount(K); prob < top; prob = next_popcount(prob)) {
        int r = dp(M, prob);
        if (r > best) best = r;
    }

    return best;
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d%d", &N, &M, &K);

        for (int i = 0; i < M; ++i)
            for (int j = 0; j < N; ++j)
                scanf("%d", &S[i][j]);

        printf("Case %d: ", ++ncase);

        int ans = solve();
        if (ans == IMPOS)
            puts("Impossible");
        else
            printf("%d\n", ans);
    }

    return 0;
}

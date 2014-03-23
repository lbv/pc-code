#include <cstdio>

#define MAXN 16

typedef unsigned int u32;

// dp[i][j] will contain the maximum priority of marrying i men with the set
// of women defined by the bitset j
int dp[MAXN + 1][1 << MAXN];

int pos[1 << MAXN];

int pri[MAXN + 1][MAXN + 1];
int N;

u32 next_popcount(u32 n)
{
    u32 c = (n & -n);
    u32 r = n+c;
    return (((r ^ n) >> 2) / c) | r;
}

void run_dp()
{
    for (int i = 1; i <= N; ++i)
        dp[1][1 << (i - 1)] = pri[1][i];

    u32 top = 1 << N;

    for (int i = 2; i <= N; ++i) {
        u32 b = 0;
        for (int j = 0; j < i; ++j)
            b |= 1 << j;

        for (u32 j = b; j < top; j = next_popcount(j)) {
            b = j;  // women remaining
            int max = 0;

            while (b != 0) {
                u32 w = b & -b;  // bit of the next woman to consider
                int idx = pos[w];

                int curr = pri[i][idx] + dp[i - 1][j & ~w];
                if (curr > max) max = curr;

                b &= ~w;
            }

            dp[i][j] = max;
        }
    }
}

void prepare()
{
    int b = 1;
    for (int i = 1; i <= MAXN; ++i) {
        pos[b] = i;
        b <<= 1;
    }
}

int main()
{
    prepare();

    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d", &N);

        for (int i = 1; i <= N; ++i)
            for (int j = 1; j <= N; ++j)
                scanf("%d", &pri[i][j]);

        run_dp();

        printf("Case %d: %d\n", ++ncase, dp[N][(1 << N) - 1]);
    }

    return 0;
}

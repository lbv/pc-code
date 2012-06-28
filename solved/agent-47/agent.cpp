#include <algorithm>
#include <cstdio>
using namespace std;

#define MAXN 15
const int INF = 1000000 * MAXN + 10;

typedef unsigned int u32;

// dp[b] will have the minimum number of shots to kill the targets
// represented by bitmask b
int dp[1 << MAXN];

// w[i][b] will have the value of the best weapon to kill target i, using
// the weapons from the people in bitmask b
int w[MAXN][1 << MAXN];

// health of targets
int H[MAXN];

// the map of weapon effectiveness between all pairs
int ws[MAXN][MAXN];

// auxiliar array to map the indices of single-bit bitmasks
int pos[1 << MAXN];

int N;

u32 next_popcount(u32 n)
{
    u32 c = (n & -n);
    u32 r = n+c;
    return (((r ^ n) >> 2) / c) | r;
}

u32 init_popcount(int n) { return (1 << n) - 1; }

void run_dp()
{
    for (int i = 0; i < N; ++i)
        w[i][0] = 1;

    u32 top = 1 << N;
    u32 r, t;
    int idx;
    for (int i = 1; i <= N; ++i) {
        for (u32 b = init_popcount(i); b < top; b = next_popcount(b)) {
            r = b;  // remainding targets
            int best = INF;

            while (r) {
                t = r & -r;  // target to consider
                idx = pos[t];

                int cur = dp[b & ~t];
                cur += H[idx]/w[idx][b & ~t];
                if (H[idx] % w[idx][b & ~t]) ++cur;

                if (cur < best) best = cur;

                r &= ~t;
            }

            dp[b] = best;

            t = b & -b;
            idx = pos[t];
            for (int j = 0; j < N; ++j)
                w[j][b] = max(ws[idx][j], w[j][b & ~t]);
        }
    }
}

void prepare()
{
    for (int i = 0; i < MAXN; ++i)
        pos[1 << i] = i;
}

int main()
{
    prepare();

    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d", &N);

        for (int i = 0; i < N; ++i) scanf("%d", &H[i]);

        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j) {
                char c;
                scanf(" %c", &c);
                ws[i][j] = c - '0';
            }

        run_dp();

        printf("Case %d: %d\n", ++ncase, dp[(1 << N) - 1]);
    }

    return 0;
}

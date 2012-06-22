#include <cstdio>

#define MAXN 16

typedef unsigned int u32;

typedef int p_t;
struct Point {
    p_t x, y;
    Point() { x=y=0; }
    Point(p_t X, p_t Y) : x(X), y(Y) {}
    bool collinear(const Point &b, const Point &c) const {
        return (b.y - y) * (c.x - x) == (c.y - y) * (b.x - x);
    }
};

u32 next_popcount(u32 n)
{
    u32 c = (n & -n);
    u32 r = n+c;
    return (((r ^ n) >> 2) / c) | r;
}
u32 init_popcount(int n) { return (1 << n) - 1; }

// dp[i] has the minimum number of moves to cover the points defined by the
// bitset i
int dp[1 << MAXN];

// col[i][j] will have the bitmask of all points that are collinear with
// points i and j
int col[MAXN + 1][MAXN + 1];

int N;

Point pts[MAXN + 1];
int pos[1 << MAXN];

void run_dp()
{
    for (int i = 1; i <= N; ++i)
        for (int j = i + 1; j <= N; ++j) {
            col[i][j] = 0;

            for (int k = 1; k <= N; ++k)
                if (pts[i].collinear(pts[j], pts[k]))
                    col[i][j] |= 1 << (k - 1);
        }

    u32 top = 1 << N;
    for (int i = 1; i <= N; ++i) {
        u32 b = init_popcount(i);

        for (u32 j = b; j < top; j = next_popcount(j)) {
            if (i == 1 || i == 2) { dp[j] = 1; continue; }

            u32 b1 = j & -j;  // bit of the first dust point to compare
            int idx1 = pos[b1];

            int best = dp[j & ~b1] + 1;

            for (u32 rem = j & ~b1; rem != 0; rem &= ~(rem & -rem)) {
                u32 b2 = rem & -rem;  // bit of the second point to compare
                int idx2 = pos[b2];

                // points that are not collinear with b1, b2
                u32 nonc = j & ~col[idx1][idx2];

                if (dp[nonc] + 1 < best) best = dp[nonc] + 1;
            }

            dp[j] = best;
        }
    }
}

void prepare()
{
    for (int i = 1; i <= MAXN; ++i)
        pos[1 << (i - 1)] = i;
}

int main()
{
    prepare();

    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d", &N);

        for (int i = 1; i <= N; ++i) {
            int x, y;
            scanf("%d%d", &x, &y);
            pts[i] = Point(x, y);
        }

        run_dp();

        printf("Case %d: %d\n", ++ncase, dp[(1 << N) - 1]);
    }

    return 0;
}

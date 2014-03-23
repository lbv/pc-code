#include <cstdio>


#define MAXN 15

#define GetFS(b) ((b) & -(b))
#define ClrFS(b) (b &= ~GetFS(b))


typedef long long    i64;
typedef unsigned int u32;


int n;
int m[MAXN][MAXN];

// dp1[i][b]: number of matchings where all pairings between the first i
// dresses and the group of shoes selected by bitmask b, are of type 1
i64 dp1[MAXN + 1][1 << MAXN];

// dp2[i][b]: number of matchings where at least one of the pairings between
// the first i dresses and the group of shoes selected by bitmask b, are of
// type 2
i64 dp2[MAXN + 1][1 << MAXN];

// fac[i]: i!
i64 fac[MAXN + 1];


u32 next_popcount(u32 n)
{
    u32 c = (n & -n);
    u32 r = n+c;
    return (((r ^ n) >> 2) / c) | r;
}
u32 init_popcount(int n) { return (1 << n) - 1; }
static const int m37pos[] = {
    32,  0,  1, 26,  2, 23, 27,  0,  3,
    16, 24, 30, 28, 11,  0, 13,  4,  7,
    17,  0, 25, 22, 31, 15, 29, 10, 12,
     6,  0, 21, 14,  9,  5, 20,  8, 19, 18
};
#define Ctz(x) (m37pos[(x) % 37])

i64 solve()
{
    u32 all = (1 << n) - 1;

    for (int i = 1; i <= n; ++i)
        for (u32 b = init_popcount(i); b <= all; b = next_popcount(b)) {
            i64 res1 = 0;
            i64 res2 = 0;

            for (u32 rest = b; rest; ClrFS(rest)) {
                u32 bit = GetFS(rest);
                int j = Ctz(bit);

                if (m[i-1][j] == 1) res1 += dp1[i - 1][b & ~bit];

                res2 += m[i-1][j] == 2 ? fac[i-1] : dp2[i - 1][b & ~bit];
            }

            dp1[i][b] = res1;
            dp2[i][b] = res2;
        }

    return dp1[n][all] + dp2[n][all];
}

void prepare()
{
    dp1[0][0] = 1;
    fac[0] = 1;

    for (int i = 1; i <= MAXN; ++i)
        fac[i] = fac[i - 1] * i;
}

int main()
{
    prepare();

    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d", &n);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                scanf("%d", &m[i][j]);

        printf("Case %d: %lld\n", ++ncase, solve());
    }

    return 0;
}

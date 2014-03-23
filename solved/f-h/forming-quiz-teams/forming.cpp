#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
using namespace std;


#define MAXN 8
#define EPS  (1e-9)

#define GetFS(b) ((b) & -(b))
#define ClrFS(b) (b &= ~GetFS(b))
static const int m37pos[] = {
    32,  0,  1, 26,  2, 23, 27,  0,  3,
    16, 24, 30, 28, 11,  0, 13,  4,  7,
    17,  0, 25, 22, 31, 15, 29, 10, 12,
     6,  0, 21, 14,  9,  5, 20,  8, 19, 18
};
#define Ctz(x) (m37pos[(x) % 37])

const int    MAXP = 2*MAXN;  // maximum number of people
const double INF  = 1e12;


typedef unsigned int u32;


int N, P;
int pts[MAXP][2];

double dis[MAXP][MAXP];  // distances between pairs of people

// dp[b]: minimised sum of distances between pairs formed from the people in
// bitmask b
double dp[1 << MAXP];


double solve()
{
    for (int i = 0; i < P; ++i)
        for (int j = i + 1; j < P; ++j) {
            int dx = pts[i][0] - pts[j][0];
            int dy = pts[i][1] - pts[j][1];
            dis[i][j] = dis[j][i] = sqrt(dx*dx + dy*dy);
        }

    u32 all = (1 << P) - 1;

    dp[0] = 0;

    for (u32 b = 1; b <= all; ++b) {
        u32 bit_cur = GetFS(b);
        int idx_cur = Ctz(bit_cur);

        double best = INF;

        for (u32 r = b & ~bit_cur; r; ClrFS(r)) {
            u32 bit_par = GetFS(r);
            int idx_par = Ctz(bit_par);

            u32 others = b & ~bit_cur & ~bit_par;
            best = min(best, dis[idx_cur][idx_par] + dp[others]);
        }

        dp[b] = best;
    }

    return dp[all] + EPS;
}

int main()
{
    int ncase = 0;
    while (true) {
        scanf("%d", &N);
        if (N == 0) break;

        P = 2*N;
        for (int i = 0; i < P; ++i)
            scanf("%*s%d%d", &pts[i][0], &pts[i][1]);

        printf("Case %d: %.2lf\n", ++ncase, solve());
    }

    return 0;
}

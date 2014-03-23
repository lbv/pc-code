#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;


#define MAXM 40
#define MAXS 300

#define Zero(v) memset((v), 0, sizeof(v))
#define Neg(v)  memset((v), -1, sizeof(v))
#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); ++v)


struct Money {
    int x, y;
    Money() {}
    Money(int X, int Y) : x(X), y(Y) {}
};
typedef vector<Money> MV;


// dec[i] has a vector of possible "Money" values that have a total of i
MV change[MAXS + 1];

// dp[i][j] will have the minimum number of coins required to make (i, j)
int dp[MAXS + 1][MAXS + 1];

bool vis[MAXS + 1][MAXS + 1];

Money coins[MAXM];
int m, S;
int ans;


void prepare()
{
    for (int x = 0; x <= MAXS; ++x)
        for (int y = 0; y <= MAXS; ++y) {
            int s2 = x*x + y*y;
            int s = sqrt(x*x + y*y);
            if (s > MAXS) break;

            if (s*s == s2)
                change[s].push_back(Money(x, y));
        }
}

void run_dp(int X, int Y)
{
    Neg(dp);
    dp[0][0] = 0;

    Zero(vis);
    vis[0][0] = true;

    int x, y;
    for (int i = 0; i < m; ++i) {
        x = coins[i].x;
        y = coins[i].y;
        if (vis[x][y]) continue;

        for (int a = x, p = 0; a <= X; ++a, ++p)
            for (int b = y, q = 0; b <= Y; ++b, ++q)
                if (dp[p][q] >= 0) {
                    if (dp[a][b] == -1 || dp[a][b] > dp[p][q] + 1)
                        dp[a][b] = dp[p][q] + 1;
                }
        vis[x][y] = true;
    }
}

bool solve()
{
    ans = -1;

    cFor (MV, m, change[S]) {
        run_dp(m->x, m->y);
        int dp_res = dp[m->x][m->y];
        if (dp_res != -1 && (ans < 0 || dp_res < ans))
            ans = dp_res;
    }

    return ans >= 0;
}

int main()
{
    prepare();

    int n;
    scanf("%d", &n);

    while (n--) {
        scanf("%d%d", &m, &S);

        int x, y;
        for (int i = 0; i < m; ++i) {
            scanf("%d%d", &x, &y);
            coins[i] = Money(x, y);
        }

        if (solve())
            printf("%d\n", ans);
        else
            puts("not possible");
    }

    return 0;
}

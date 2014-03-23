#include <cstdio>
#include <cstring>

#define MAXN 50

#define Zero(v) memset(v, 0, sizeof(v))

typedef unsigned long long u64;

// dp[i][j] will contain the number of ways to choose i objects using
// objects up to objs[j]
u64 dp[MAXN + 1][MAXN + 1];

int objs[MAXN + 1];       // list of objects
bool used[MAXN + 1];  // indicates if a certain object is present
int cnt[MAXN + 1];    // number of occurrences of the objects
int nobj;

int n, m;

void run_dp()
{
    Zero(dp);
    for (int j = 0; j <= nobj; ++j)
        dp[0][j] = 1;

    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= nobj; ++j) {
            int o = objs[j];
            for (int k = 0; k <= cnt[o] && i - k >= 0; ++k)
                dp[i][j] += dp[i-k][j-1];
        }
}

int main()
{
    int ncase = 0;
    while (true) {
        scanf("%d%d", &n, &m);
        if (n == 0) break;

        Zero(used);
        Zero(cnt);
        nobj = 0;

        for (int i = 0; i < n; ++i) {
            int l;
            scanf("%d", &l);
            if (! used[l]) {
                objs[++nobj] = l;
                used[l] = true;
            }
            ++cnt[l];
        }

        run_dp();

        printf("Case %d:\n", ++ncase);
        while (m--) {
            int r;
            scanf("%d", &r);
            printf("%llu\n", dp[r][nobj]);
        }
    }

    return 0;
}

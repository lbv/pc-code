#include <cstdio>

#define MAXN 1000
#define INF  1010

int N, K;
int tot;
int ds[MAXN + 1];

// returns the number of stops necessary if any day you can walk the
// distance m at most
int f(int m)
{
    int w = 0;
    int s = 0;
    for (int i = 0; i <= N; ++i) {
        w += ds[i];
        if (w > m) {
            ++s;
            w = ds[i];
            if (w > m) return INF;
        }
    }
    return s;
}

int solve()
{
    int hi = tot;
    int lo = 0;
    int ans;

    while (true) {
        ans = (hi + lo) / 2;

        int stops = f(ans);

        if (stops <= K && f(ans - 1) > K) break;

        if (stops > K) lo = ans + 1;
        else hi = ans - 1;
    }

    return ans;
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d", &N, &K);

        tot = 0;
        for (int i = 0; i <= N; ++i) {
            scanf("%d", &ds[i]);
            tot += ds[i];
        }

        int ans = solve();

        printf("Case %d: %d\n", ++ncase, ans);

        int w = 0;
        int n = K + 1;  // number of days to walk
        for (int i = 0; i <= N; ++i) {
            if (N - i + 2 == n || w + ds[i] > ans) {
                printf("%d\n", w);
                w = 0;
                --n;
            }
            w += ds[i];
        }
        printf("%d\n", w);
    }

    return 0;
}

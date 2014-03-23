#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;


#define MAXN 100

#define Zero(v) memset((v), 0, sizeof(v))


int N, D;
int rocks[MAXN + 2];
int n;

bool vis[MAXN + 2];


bool check(int d)
{
    Zero(vis);
    int from = 0, to = 0;

    for (int i = 1; i < n; ++i) {
        if (rocks[i] - rocks[from] <= d) { to = i; continue; }

        vis[to] = true;
        from = to, to = i;
        if (rocks[to] - rocks[from] > d) return false;
    }

    vis[n-1] = false;

    from = 0;
    for (int i = 1; i < n; ++i) {
        if (vis[i]) continue;
        if (rocks[i] - rocks[from] > d) return false;
        from = i;
    }

    return true;
}

int shortest()
{
    int lo = 0, hi = rocks[n - 1] - rocks[0];

    while (lo <= hi) {
        int mid = (hi + lo) / 2;
        if (check(mid)) hi = mid - 1;
        else lo = mid + 1;
    }
    return lo;
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d", &N, &D);

        int ans = 0;
        n = 1;
        rocks[0] = 0;

        for (int i = 0; i < N; ++i) {
            char S;
            int M;
            scanf(" %c-%d", &S, &M);

            rocks[n++] = M;
            if (S == 'B') {
                ans = max(ans, shortest());
                n = 1;
                rocks[0] = M;
            }
        }
        rocks[n++] = D;
        ans = max(ans, shortest());

        printf("Case %d: %d\n", ++ncase, ans);
    }

    return 0;
}

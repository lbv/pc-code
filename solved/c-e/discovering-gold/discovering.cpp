#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

#define Zero(v) memset(v, 0, sizeof(v))

#define MAXN 100

double e[MAXN + 1];  // Expected value
int g[MAXN + 1];     // Amount of gold

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        int N;
        scanf("%d", &N);

        Zero(e);

        for (int i = 1; i <= N; ++i)
            scanf("%d", &g[i]);

        e[1] = 1.0;

        double ans = 0.0;

        for (int i = 1; i <= N; ++i) {
            ans += g[i] * e[i];

            int end  = min(N, i + 6);
            double chance = e[i] / (end - i);
            for (int j = i + 1; j <= end; ++j)
                e[j] += chance;
        }

        printf("Case %d: %.8lf\n", ++ncase, ans);
    }
}

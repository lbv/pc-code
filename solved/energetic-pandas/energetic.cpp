#include <algorithm>
#include <cstdio>
using namespace std;

typedef long long i64;

#define MOD  1000000007
#define MAXN 1000

int w[MAXN + 1];  // weight of bamboos
int c[MAXN + 1];  // capacities of the pandas

int N;

int solve()
{
    sort(w, w + N);
    sort(c, c + N);

    i64 count = 1;

    int b = 0;  // index of the bamboo weight we're looking at
    for (int p = 0; p < N; p++) {
        while (b < N && w[b] <= c[p]) b++;

        if (p >= b) return 0;
        count = count * (b - p) % MOD;
    }

    return count;
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 1;
    while (T--) {
        scanf("%d", &N);

        for (int i = 0; i < N; i++) scanf("%d", &w[i]);
        for (int i = 0; i < N; i++) scanf("%d", &c[i]);

        printf("Case %d: %d\n", ncase++, solve());
    }

    return 0;
}

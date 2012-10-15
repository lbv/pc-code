#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;


#define MAXN 100
#define MAXS 100000

#define Zero(v) memset((v), 0, sizeof(v))
#define GetFS(b) ((b) & -(b))


struct Bit {
    int f[MAXS + 1]; int n;
    void init(int N) { n=N; Zero(f); }
    void add(int i, int v) { while (i <= n) { f[i] += v; i += GetFS(i); } }
    int query(int i) {
        int r = 0; while (i) { r += f[i]; i -= GetFS(i); } return r; }
};


int N;
int sticks[MAXN];
Bit tree;


int solve()
{
    sort(sticks, sticks + N);
    int hi = sticks[N - 1];

    int ans = 0;
    tree.init(sticks[N - 1]);

    for (int i = N - 4; i >= 2; --i) {
        int a = i + 1;
        for (int b = a + 1; b < N; ++b)
            for (int c = b + 1; c < N; ++c) {
                int v = max(1, sticks[c] - (sticks[a] + sticks[b]));
                tree.add(v, 1);
            }

        for (int j = i - 1; j >= 1; --j)
            for (int k = j - 1; k >= 0; --k) {
                int v = min(hi, sticks[i] + sticks[j] + sticks[k]);
                ans += tree.query(v - 1);
            }
    }

    return ans;
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d", &N);

        for (int i = 0; i < N; ++i)
            scanf("%d", &sticks[i]);

        printf("Case %d: %d\n", ++ncase, solve());
    }

    return 0;
}

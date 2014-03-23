#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
using namespace std;

#define Zero(v) memset(v, 0, sizeof(v))
#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); ++v)

#define MAXN 10000

typedef vector<int> IV;

int parent[MAXN + 1];
IV child[MAXN + 1];
int boys[MAXN + 1];
int n;
int ans;

void dfs(int v)
{
    cFor (IV, c, child[v])
        dfs(*c);

    int p = parent[v];

    if (boys[v] != 1) {
        ans += abs(boys[v] - 1);
        boys[p] += boys[v] - 1;
    }
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d", &n);

        Zero(parent);

        for (int i = 0; i < n; ++i) {
            int v, nboys, d;
            scanf("%d%d%d", &v, &nboys, &d);
            boys[v] = nboys;

            child[v].clear();
            for (int j = 0; j < d; ++j) {
                int city;
                scanf("%d", &city);
                parent[city] = v;
                child[v].push_back(city);
            }
        }

        int root = 0;
        for (int i = 1; i <= n; ++i)
            if (parent[i] == 0) {
                root = i;
                break;
            }

        ans = 0;
        dfs(root);

        printf("Case %d: %d\n", ++ncase, ans);
    }

    return 0;
}

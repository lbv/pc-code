#include <algorithm>
#include <cstdio>
using namespace std;

#define MAXN 100

int ns[MAXN + 1];
int map[MAXN + 1];

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        int n;
        scanf("%d", &n);

        for (int i = 1; i <= n; ++i) {
            scanf("%d", &ns[i]);
            map[ns[i]] = i;
        }

        int ans = 0;

        for (int i = 1; i <= n; ++i) {
            if (ns[i] != i) {
                int b = map[i];
                swap(ns[i], ns[b]);
                map[i] = i;
                map[ns[b]] = b;
                ++ans;
            }
        }

        printf("Case %d: %d\n", ++ncase, ans);
    }

    return 0;
}

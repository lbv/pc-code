#include <algorithm>
#include <cstdio>
using namespace std;

#define MAXN 20000

int ns[MAXN];
int n;

int main()
{
    int t;
    scanf("%d", &t);

    while (t--) {
        scanf("%d", &n);

        for (int i = 0; i < n; ++i)
            scanf("%d", &ns[i]);

        sort(ns, ns + n);

        int ans = 0;
        for (int i = n -1, j = 1; i >= 0; --i, ++j)
            if (j % 3 == 0)
                ans += ns[i];

        printf("%d\n", ans);
    }

    return 0;
}

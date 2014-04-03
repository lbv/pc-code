#include <cstdio>

#define MAXN 100000

int ns[MAXN + 1];
int n;

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d", &n);

        for (int i = 1; i <= n; ++i) {
            scanf("%d", &ns[i]);
            ns[i] ^= ns[i-1];
        }

        printf("Case %d:\n", ++ncase);

        int q, u, v;
        scanf("%d", &q);
        while (q--) {
            scanf("%d%d", &u, &v);
            printf("%d\n", ns[v] ^ ns[u - 1]);
        }
    }

    return 0;
}

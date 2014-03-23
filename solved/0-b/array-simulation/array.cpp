#include <algorithm>
#include <cstdio>
using namespace std;

#define MAXN 100

int a[MAXN];

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        int n, m;
        scanf("%d%d", &n, &m);

        for (int i = 0; i < n; ++i) scanf("%d", &a[i]);

        while (m--) {
            char c;
            scanf(" %c", &c);

            int d;
            switch (c) {
            case 'S':
                scanf("%d", &d);
                for (int i = 0; i < n; ++i) a[i] += d;
                break;

            case 'M':
                scanf("%d", &d);
                for (int i = 0; i < n; ++i) a[i] *= d;
                break;

            case 'D':
                scanf("%d", &d);
                for (int i = 0; i < n; ++i) a[i] /= d;
                break;

            case 'R':
                for (int i = 0, j = n - 1; i < j; ++i, --j) swap(a[i], a[j]);
                break;

            case 'P':
                int y, z;
                scanf("%d%d", &y, &z);
                swap(a[y], a[z]);
                break;
            }
        }

        printf("Case %d:\n%d", ++ncase, a[0]);
        for (int i = 1; i < n; ++i)
            printf(" %d", a[i]);
        putchar('\n');
    }

    return 0;
}

#include <cstdio>
#include <cstdlib>
#include <cstring>

#define MAXN 3000

#define Zero(v) memset(v, 0, sizeof(v))

int n;
bool map[MAXN + 1];

int main()
{
    while (true) {
        if (scanf("%d", &n) != 1) break;

        int prev = 0;
        int u = 0;
        int a, dif;
        bool first = true;
        Zero(map);

        for (int i = 0; i < n; ++i) {
            scanf("%d", &a);

            if (first) {
                prev = a;
                first = false;
                continue;
            }

            dif = abs(a - prev);
            if (dif > 0 && dif <= n - 1 && !map[dif]) {
                ++u;
                map[dif] = true;
            }
            prev = a;
        }

        if (u == n - 1) puts("Jolly");
        else puts("Not jolly");
    }

    return 0;
}

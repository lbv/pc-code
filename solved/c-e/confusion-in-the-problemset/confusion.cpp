#include <cstdio>
#include <cstring>


#define MAXN 10000

#define Zero(v) memset((v), 0, sizeof(v))


bool used[MAXN];
int n;


int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d", &n);

        Zero(used);
        bool valid = true;

        for (int i = 0; i < n; ++i) {
            int x;
            scanf("%d", &x);

            if (! valid) continue;
            if (x >= n) { valid = false; continue; }

            if (! used[x]) {
                used[x] = true;
                continue;
            }

            int idx = n - 1 - x;

            if (! used[idx]) {
                used[idx] = true;
                continue;
            }

            valid = false;
        }

        printf("Case %d: ", ++ncase);
        if (valid)
            puts("yes");
        else
            puts("no");
    }

    return 0;
}

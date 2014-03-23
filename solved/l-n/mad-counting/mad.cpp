#include <cstdio>
#include <cstring>

#define Zero(v) memset(v, 0, sizeof(v))

#define MAXR 1000000

int replies[MAXR + 1];

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        Zero(replies);

        int N, r;
        scanf("%d", &N);

        int ans = 0;
        while (N--) {
            scanf("%d", &r);
            if (replies[r] % (r + 1) == 0)
                ans += r + 1;
            ++replies[r];
        }

        printf("Case %d: %d\n", ++ncase, ans);
    }

    return 0;
}

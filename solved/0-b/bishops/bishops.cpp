#include <cstdio>
#include <cstdlib>

int main() {
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        int r1, c1, r2, c2;
        scanf("%d%d%d%d", &r1, &c1, &r2, &c2);

        if (((r1+c1) & 1) != ((r2+c2) & 1)) {
            printf("Case %d: impossible\n", ++ncase);
            continue;
        }
        int ans = abs(r1-r2) == abs(c1-c2) ? 1 : 2;
        printf("Case %d: %d\n", ++ncase, ans);
    }

    return 0;
}

#include <cstdio>

int n, f;

int main()
{
    scanf("%d", &n);

    while (n--) {
        scanf("%d", &f);

        int ans = 0;
        int s, e;  // size, environment friendliness

        while (f--) {
            scanf("%d %*d %d", &s, &e);
            ans += s*e;
        }

        printf("%d\n", ans);
    }

    return 0;
}

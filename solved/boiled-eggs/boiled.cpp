#include <cstdio>

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        int n, P, Q;
        scanf("%d%d%d", &n, &P, &Q);

        int gm = 0;  // weight of eggs used
        int u  = 0;  // eggs used
        int w;

        while (n--) {
            scanf("%d", &w);
            if (u < P && gm + w <= Q) {
                ++u;
                gm += w;
            }
            else {
                while(n--) scanf("%*d");
                break;
            }
        }

        printf("Case %d: %d\n", ++ncase, u);
    }

    return 0;
}

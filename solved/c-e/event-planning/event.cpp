#include <cstdio>

#define INF 500010

int N, B, H, W, p, a;
int ans;

int main()
{
    while (true) {
        if (scanf("%d%d%d%d", &N, &B, &H, &W) != 4) break;

        ans = INF;

        while (H--) {
            scanf("%d", &p);

            for (int i = 0; i < W; ++i) {
                scanf("%d", &a);

                if (a >= N && p*N < ans)
                    ans = p*N;
            }
        }

        if (ans <= B)
            printf("%d\n", ans);
        else
            puts("stay home");
    }

    return 0;
}

#include <cstdio>
#include <cstring>


#define MAXN 3650

#define Zero(v) memset(v, 0, sizeof(v))


int N, P, h;
bool hartals[MAXN + 1];


int main()
{
    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%d%d", &N, &P);

        Zero(hartals);

        while (P--) {
            scanf("%d", &h);

            if (hartals[h]) continue;
            for (int i = h; i <= N; i += h)
                hartals[i] = true;
        }

        int ans = 0;
        for (int i = 1; i <= N; i += 7)
            for (int j = i, J = i + 4; j <= J && j <= N; ++j)
                if (hartals[j]) ++ans;

        printf("%d\n", ans);
    }

    return 0;
}

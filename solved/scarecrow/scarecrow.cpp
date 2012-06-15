#include <cstdio>
#include <cstring>

#define MAXN 100

#define Zero(v) memset(v, 0, sizeof(v))

// map[i] is true if the cell i is covered by a scarecrow
bool map[MAXN + 2];

int N, ans;

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d", &N);

        Zero(map);
        ans = 0;

        char c;

        for (int i = 0; i < N; ++i) {
            scanf(" %c", &c);
            if (c == '.' && ! map[i]) {
                ++ans;
                map[i + 1] = map[i + 2] = true;
            }
        }

        printf("Case %d: %d\n", ++ncase, ans);
    }

    return 0;
}

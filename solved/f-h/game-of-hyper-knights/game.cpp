#include <cstdio>
#include <cstring>


#define MAXN 500

#define Zero(v) memset((v), 0, sizeof(v))


int n;

// g[i][j]: grundy number for position i, j
int g[2*MAXN + 1][2*MAXN + 1];

bool used[MAXN + 1];


bool valid_pos(int r, int c)
{
    return r >= 0 && c >= 0;
}

void prepare()
{
    int nim;
    for (int d = 1, D = 2*MAXN; d <= D; ++d)
        for (int i = 0; i <= d; ++i) {
            int j = d - i;

            Zero(used);
            if (valid_pos(i + 1, j - 2))
                used[g[i + 1][j - 2]] = true;

            if (valid_pos(i - 1, j - 3))
                used[g[i - 1][j - 3]] = true;

            if (valid_pos(i - 1, j - 2))
                used[g[i - 1][j - 2]] = true;

            if (valid_pos(i - 2, j - 1))
                used[g[i - 2][j - 1]] = true;

            if (valid_pos(i - 2, j + 1))
                used[g[i - 2][j + 1]] = true;

            if (valid_pos(i - 3, j - 1))
                used[g[i - 3][j - 1]] = true;

            for (nim = 0; used[nim]; ++nim) ;
            g[i][j] = nim;
        }
}

int main()
{
    prepare();

    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d", &n);

        int nim = 0;
        while (n--) {
            int x, y;
            scanf("%d%d", &x, &y);

            nim ^= g[x][y];
        }

        printf("Case %d: ", ++ncase);
        if (nim)
            puts("Alice");
        else
            puts("Bob");
    }

    return 0;
}

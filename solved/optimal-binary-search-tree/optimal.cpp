#include <cstdio>


#define MAXN 250
const int INF = MAXN * MAXN * 100 + 10;


int n;
int f[MAXN];
int ps[MAXN];
int cost[MAXN][MAXN];
int root[MAXN][MAXN];

int w(int a, int b)
{
    return a > 0 ? ps[b] - ps[a - 1] : ps[b];
}

void run_dp()
{
    ps[0] = f[0];
    for (int i = 1; i < n; ++i)
        ps[i] = ps[i - 1] + f[i];

    for (int l = 2; l <= n; ++l) {
        for (int i = 0, j = i + l - 1; j < n; ++i, ++j) {
            int a = root[i][j - 1];
            int b = root[i + 1][j];

            int c = INF;
            int r = i;
            for (int k = a; k <= b; ++k) {
                int x = 0;
                if (k > i)
                    x += cost[i][k - 1] + w(i, k - 1);
                if (k < j)
                    x += cost[k + 1][j] + w(k + 1, j);

                if (x < c) {
                    r = k;
                    c = x;
                }
            }
            cost[i][j] = c;
            root[i][j] = r;
        }
    }
}

void prepare()
{
    for (int i = 0; i < MAXN; ++i)
        root[i][i] = i;
}

int main()
{
    prepare();

    while (true) {
        if (scanf("%d", &n) != 1) break;

        for (int i = 0; i < n; ++i)
            scanf("%d", &f[i]);

        run_dp();

        printf("%d\n", cost[0][n - 1]);
    }

    return 0;
}

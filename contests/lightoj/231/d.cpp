#include <cstdio>
#include <cstring>


#define MAXR 20
#define MAXC 20

#define Zero(v) memset((v), 0, sizeof(v))


int R, C;
char grid[MAXR][MAXC + 1];
bool vis[MAXR][MAXC];


bool in_fire(int r, int c)
{
    return r >= 0 && r < R && c >= 0 && c < C && grid[r][c] == '#';
}

int dfs(int i, int j)
{
    vis[i][j] = true;
    int a = 1;

    for (int x = -1; x <= 1; ++x)
        for (int y = -1; y <= 1; ++y) {
            if (x == 0 && y == 0) continue;
            int p = i + x, q = j + y;
            if (in_fire(p, q) && ! vis[p][q])
                a += dfs(p, q);
        }

    return a;
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d", &R, &C);

        for (int i = 0; i < R; ++i) scanf("%s", grid[i]);

        Zero(vis);
        int area = 0;
        int fires = 0;

        for (int i = 0; i < R; ++i)
            for (int j = 0; j < C; ++j)
                if (grid[i][j] == '#' && ! vis[i][j]) {
                    int a = dfs(i, j);
                    ++fires;
                    if (a > area) area = a;
                }

        printf("Case %d: %d %d\n", ++ncase, fires, area);
    }

    return 0;
}

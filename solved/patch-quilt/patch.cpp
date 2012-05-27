#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

#define Zero(v) memset(v, 0, sizeof(v))

#define MAXR 30
#define MAXC 30
#define MAX_NAME 15

struct Pos
{
    int r, c;
    Pos(int R, int C) : r(R), c(C) {}
    Pos() {}
};
typedef vector<Pos> PV;

char name[MAX_NAME + 1];
int R, C, N, nlen;
char quilt[MAXR][MAXC + 1];

Pos trail[MAX_NAME];
PV sol;
bool visit[MAXR][MAXC][MAX_NAME];

bool valid_pos(const Pos &p)
{
    return p.r >= 0 && p.r < R && p.c >= 0 && p.c < C;
}

void print_solution()
{
    printf("(%d,%d)", sol[0].r + 1, sol[0].c + 1);
    for (int i = 1; i < nlen; ++i) {
        int dr = sol[i].r - sol[i - 1].r;
        int dc = sol[i].c - sol[i - 1].c;

        if (dr == -1 && dc == -1)
            printf(", UL");
        else if (dr == -1 && dc == 0)
            printf(", U");
        else if (dr == -1 && dc == 1)
            printf(", UR");
        else if (dr == 0 && dc == -1)
            printf(", L");
        else if (dr == 0 && dc == 0)
            printf(", *");
        else if (dr == 0 && dc == 1)
            printf(", R");
        else if (dr == 1 && dc == -1)
            printf(", DL");
        else if (dr == 1 && dc == 0)
            printf(", D");
        else if (dr == 1 && dc == 1)
            printf(", DR");
    }
    putchar('\n');
}


void dfs(int r, int c, int n)
{
    if (visit[r][c][n]) return;
    visit[r][c][n] = true;

    if (quilt[r][c] != name[n]) return;

    trail[n++] = Pos(r, c);

    if (n == nlen) {
        for (int i = 0; i < nlen; ++i)
            sol.push_back(trail[i]);
        return;
    }

    for (int i = -1; i <= 1; ++i)
        for (int j = -1; j <= 1; ++j) {
            Pos p(r + i, c + j);
            if (! valid_pos(p)) continue;

            dfs(p.r, p.c, n);
        }
}

void solve()
{
    Zero(visit);
    sol.clear();
    for (int i = 0; i < R; ++i)
        for (int j = 0; j < C; ++j)
            dfs(i, j, 0);
}

int main(void)
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d", &R, &C);

        for (int i = 0; i < R; ++i)
            scanf("%s", quilt[i]);

        scanf("%d", &N);

        printf("Case %d:\n", ++ncase);
        while (N--) {
            scanf("%s", name);
            nlen = strlen(name);

            solve();

            if (sol.size() == 0)
                printf("%s not found\n", name);
            else {
                printf("%s found: ", name);
                print_solution();
            }
        }
    }

    return 0;
}

#include <cmath>
#include <cstdio>
#include <cstring>


#define MAXR 100
#define MAXC 100

#define Neg(v)  memset((v), -1, sizeof(v))

const int MAX_X = MAXR * 2;
const int MAX_Y = MAXC * 2;


int  R, C;
int  Q, x, y;
char grid[MAXR][MAXC + 1];

double curr;
double ans[MAX_X + 1][MAX_Y + 1];

// memo[x][y]: coordinates of the position that has the answer for (x, y)
int memo[MAX_X + 1][MAX_Y + 1][2];

const double pi = acos(-1);
const double a1 = pi / 4;    // area of one "closed" corner from a tile
const double a2 = 4 - pi/2;  // area of the "middle section" of a tile


bool is_odd(int n) { return n % 2 != 0; }

bool is_valid(int r, int c)
{
    return r >= 0 && r <= 2*R && c >= 0 && c <= 2*C;
}

bool should_visit(int r, int c)
{
    return is_valid(r, c) && memo[r][c][0] < 0;
}

void dfs(int r, int c)
{
    memo[r][c][0] = x;
    memo[r][c][1] = y;

    if (is_odd(r) && is_odd(c)) {
        curr += a2;
        if (grid[r/2][c/2] == '0') {
            if (should_visit(r - 1, c + 1)) dfs(r-1, c+1);
            if (should_visit(r + 1, c - 1)) dfs(r+1, c-1);
        }
        else {
            if (should_visit(r - 1, c - 1)) dfs(r-1, c-1);
            if (should_visit(r + 1, c + 1)) dfs(r+1, c+1);
        }
        return;
    }

    if (is_valid(r-1, c-1)) {
        int p = (r-1) / 2, q = (c-1)/2;
        if (grid[p][q] == '0') curr += a1;
        else if (should_visit(r-1, c-1)) dfs(r-1, c-1);
    }
    if (is_valid(r-1, c+1)) {
        int p = (r-1) / 2, q = (c+1)/2;
        if (grid[p][q] == '1') curr += a1;
        else if (should_visit(r-1, c+1)) dfs(r-1, c+1);
    }
    if (is_valid(r+1, c-1)) {
        int p = (r+1) / 2, q = (c-1)/2;
        if (grid[p][q] == '1') curr += a1;
        else if (should_visit(r+1, c-1)) dfs(r+1, c-1);
    }
    if (is_valid(r+1, c+1)) {
        int p = (r+1) / 2, q = (c+1)/2;
        if (grid[p][q] == '0') curr += a1;
        else if (should_visit(r+1, c+1)) dfs(r+1, c+1);
    }
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d", &R, &C);
        for (int i = 0; i < R; ++i) scanf("%s", grid[i]);

        printf("Case %d:\n", ++ncase);

        Neg(memo);
        scanf("%d", &Q);
        while (Q--) {
            scanf("%d%d", &x, &y);

            if (is_odd(x + y)) { puts("0"); continue; }

            if (memo[x][y][0] >= 0) {
                int ax = memo[x][y][0];
                int ay = memo[x][y][1];
                printf("%.8lf\n", ans[ax][ay]);
                continue;
            }

            curr = 0.0;
            dfs(x, y);
            ans[x][y] = curr;
            printf("%.8lf\n", curr);
        }
    }

    return 0;
}

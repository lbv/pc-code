#include <cstdio>
#include <cstring>


#define MAXN 100

#define Zero(v) memset((v), 0, sizeof(v))


typedef unsigned int u32;


struct LineReader {
    char b; LineReader() { read(); }
    void read() { int r = fgetc_unlocked(stdin); b = r == EOF ? 0 : r; }
    void skip() { while (b > 0 && b <= 32 && b != 10) read(); }
    void skip_line() { skip(); if (b == 10) { read(); skip(); } }
    bool has_next() { skip(); return b > 0 && b != 10; }
    bool eof() { skip(); return b == 0; }

    u32 next_u32() {
        u32 v = 0; for (skip(); b > 32; read()) v = v*10 + b-48; return v; }
};


int n;
int grid[MAXN][MAXN];
int par[MAXN];
bool vis[MAXN][MAXN];

const int dd[4][2] = {
    {  0, -1 },
    {  0,  1 },
    {  1,  0 },
    { -1,  0 }
};


bool valid(int r, int c)
{
    return r >= 0 && r < n && c >= 0 && c < n;
}

int dfs(int i, int j)
{
    vis[i][j] = true;
    int cells = 1;

    for (int k = 0; k < 4; ++k) {
        int r = i + dd[k][0];
        int c = j + dd[k][1];

        if (valid(r, c) && grid[r][c] == grid[i][j] && ! vis[r][c])
            cells += dfs(r, c);
    }

    return cells;
}

bool solve()
{
    Zero(vis);
    Zero(par);

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (! vis[i][j]) {
                int p = grid[i][j];
                if (par[p] != 0) return false;
                par[p] = dfs(i, j);
            }

    for (int i = 0; i < n; ++i)
        if (par[i] != n) return false;
    return true;
}

int main()
{
    LineReader lr;

    while (true) {
        n = lr.next_u32();
        lr.skip_line();

        if (n == 0) break;

        Zero(grid);
        for (int k = 1; k < n; ++k) {
            while (lr.has_next()) {
                int i = lr.next_u32();
                if (! lr.has_next()) break;
                int j = lr.next_u32();

                --i; --j;
                if (valid(i, j))
                    grid[i][j] = k;
            }
            lr.skip_line();
        }
        if (solve())
            puts("good");
        else
            puts("wrong");
    }

    return 0;
}

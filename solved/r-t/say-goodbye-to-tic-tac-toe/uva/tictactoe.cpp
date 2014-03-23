#include <cstdio>
#include <cstring>


#define MAXN 100

#define Zero(v) memset((v), 0, sizeof(v))


char grid[MAXN + 1];
int len;

// g[i][a][b]: grundy number for a game of i consecutive free cells and
// with symbol 'a' to the left, and 'b' to the right
int g[MAXN][3][3];

// s[i]: index of the cell where a block of free cells that include i starts
int s[MAXN];
// e[i]: index of the cell where a block of free cells that include i ends
int e[MAXN];

bool used[MAXN + 1];


void prepare()
{
    int nim;
    for (int i = 1; i <= MAXN; ++i)
        for (int a = 0; a < 3; ++a)
            for (int b = 0; b < 3; ++b) {
                Zero(used);
                for (int j = 0; j < i; ++j) {
                    if (! (j == 0 && a == 1) && !(j == i - 1 && b == 1)) {
                        nim = g[j][a][1] ^ g[i - j - 1][1][b];
                        used[nim] = true;
                    }
                    if (! (j == 0 && a == 2) && !(j == i - 1 && b == 2)) {
                        nim = g[j][a][2] ^ g[i - j - 1][2][b];
                        used[nim] = true;
                    }
                }

                nim = 0;
                while (used[nim]) ++nim;
                g[i][a][b] = nim;
            }
}

int symbol(char c)
{
    if (c == 'X') return 1;
    if (c == 'O') return 2;
    return 0;
}

bool solve()
{
    int moves = 0;

    int lt = 0;
    for (int i = 0; i < len; ++i) {
        if (grid[i] == '.') s[i] = lt;
        else {
            lt = i + 1;
            ++moves;
        }
    }

    int rt = len;
    for (int i = len - 1; i >= 0; --i) {
        if (grid[i] == '.') e[i] = rt;
        else rt = i;
    }

    int nim = 0;
    for (int i = 0; i < len; ++i) {
        if (grid[i] != '.') continue;

        int cells = e[i] - s[i];
        lt = s[i] > 0 ? symbol(grid[s[i] - 1]) : 0;
        rt = e[i] < len ? symbol(grid[e[i]]) : 0;

        nim ^= g[cells][lt][rt];
        i = e[i];
    }

    return moves % 2 == 0 ? nim != 0 : nim == 0;
}

int main()
{
    prepare();

    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%s", grid);
        len = strlen(grid);

        if (solve())
            puts("Possible.");
        else
            puts("Impossible.");
    }

    return 0;
}

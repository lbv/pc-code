#include <cstdio>
#include <cstring>


#define MAXLEN 15

#define Zero(v) memset((v), 0, sizeof(v))


char board[4][5];
int  m;
int  score;
char str[MAXLEN + 1];
int  len;

const int sc_table[] = {
     0,  0,  0,  1,  1,
     2,  3,  5, 11, 11,
    11, 11, 11, 11, 11, 11 };


bool is_valid(int r, int c)
{
    return r >= 0 && r < 4 && c >= 0 && c < 4;
}

bool dfs(int r, int c, int p)
{
    if (board[r][c] != str[p]) return false;
    if (p == len - 1) return true;

    board[r][c] = '*';
    for (int i = -1; i <= 1; ++i)
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue;
            int r2 = r + i, c2 = c + j;
            if (is_valid(r2, c2) && dfs(r2, c2, p + 1)) {
                board[r][c] = str[p];
                return true;
            }
        }
    board[r][c] = str[p];
    return false;
}

void process()
{
    len = strlen(str);
    if (len < 3) return;

    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            if (board[i][j] == str[0] && dfs(i, j, 0)) {
                score += sc_table[len];
                return;
            }
}

int main()
{
    int n;
    scanf("%d", &n);

    int ncase = 0;
    while (n--) {
        for (int i = 0; i < 4; ++i)
            scanf("%s", board[i]);

        score = 0;
        scanf("%d", &m);
        while (m--) {
            scanf("%s", str);
            process();
        }

        printf("PUZZLE #%d: %d\n", ++ncase, score);
    }

    return 0;
}

#include <cstdio>
#include <cstring>

#define MAXLEN (9*8)

#define Zero(v) memset(v, 0, sizeof(v))

char line[MAXLEN + 1];
char board[8][8];
bool atk[8][8];

const int knight[8][2] = {
    { +1, +2 },
    { -1, +2 },
    { +1, -2 },
    { -1, -2 },
    { +2, +1 },
    { -2, +1 },
    { +2, -1 },
    { -2, -1 },
};

bool valid_pos(int r, int c)
{
    return r >= 0 && r < 8 && c >= 0 && c < 8;
}

bool unoc_pos(int r, int c)
{
    return valid_pos(r, c) && board[r][c] == '.';
}

void fill_board()
{
    int r = 0, c = 0;

    for (int i = 0, I = strlen(line); i < I; ++i) {
        if (line[i] == '/') ++r, c = 0;
        else if (line[i] >= '1' && line[i] <= '8')
            for (int j = 0, J = line[i] - '0'; j < J; ++j)
                board[r][c++] = '.';
        else
            board[r][c++] = line[i];
    }
}

void handle_bishop(int i, int j) {
    for (int r = i + 1, c = j + 1; unoc_pos(r, c); ++r, ++c)
        atk[r][c] = true;
    for (int r = i + 1, c = j - 1; unoc_pos(r, c); ++r, --c)
        atk[r][c] = true;
    for (int r = i - 1, c = j - 1; unoc_pos(r, c); --r, --c)
        atk[r][c] = true;
    for (int r = i - 1, c = j + 1; unoc_pos(r, c); --r, ++c)
        atk[r][c] = true;
}

void handle_rook(int i, int j) {
    for (int r = i - 1, c = j; unoc_pos(r, c); --r)
        atk[r][c] = true;
    for (int r = i + 1, c = j; unoc_pos(r, c); ++r)
        atk[r][c] = true;
    for (int r = i, c = j - 1; unoc_pos(r, c); --c)
        atk[r][c] = true;
    for (int r = i, c = j + 1; unoc_pos(r, c); ++c)
        atk[r][c] = true;
}

void find_attacked()
{
    Zero(atk);
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            switch (board[i][j]) {
            case 'p':
                if (valid_pos(i + 1, j - 1)) atk[i + 1][j - 1] = true;
                if (valid_pos(i + 1, j + 1)) atk[i + 1][j + 1] = true;
                break;
            case 'P':
                if (valid_pos(i - 1, j - 1)) atk[i - 1][j - 1] = true;
                if (valid_pos(i - 1, j + 1)) atk[i - 1][j + 1] = true;
                break;
            case 'n':
            case 'N':
                for (int k = 0; k < 8; ++k) {
                    int r = i + knight[k][0];
                    int c = j + knight[k][1];
                    if (valid_pos(r, c)) atk[r][c] = true;
                }
                break;
            case 'b':
            case 'B':
                handle_bishop(i, j);
                break;
            case 'r':
            case 'R':
                handle_rook(i, j);
                break;
            case 'q':
            case 'Q':
                handle_bishop(i, j);
                handle_rook(i, j);
                break;
            case 'k':
            case 'K':
                for (int x = -1; x <= 1; ++x)
                    for (int y = -1; y <= 1; ++y)
                        if (valid_pos(i + x, j + y))
                            atk[i + x][j + y] = true;
                break;
            }
}

int free_positions()
{
    int ans = 0;
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            if (board[i][j] == '.' && !atk[i][j])
                ++ans;
    return ans;
}

int main()
{
    while (true) {
        if (scanf("%s", line) != 1) break;

        fill_board();
        find_attacked();
        printf("%d\n", free_positions());
    }

    return 0;
}

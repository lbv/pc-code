#include <algorithm>
#include <cstdio>
using namespace std;


const int INF = 9 * 7 * 7 + 10;


char board[7][10];
const int sc_table[7][7] = {
    { 0, 0, 9, 9, 9, 0, 0 },
    { 0, 0, 4, 4, 4, 0, 0 },
    { 9, 4, 1, 1, 1, 4, 9 },
    { 9, 4, 1, 0, 1, 4, 9 },
    { 9, 4, 1, 1, 1, 4, 9 },
    { 0, 0, 4, 4, 4, 0, 0 },
    { 0, 0, 9, 9, 9, 0, 0 }
};

const int dd[4][2] = {
    { -1,  0 },
    {  1,  0 },
    {  0,  1 },
    {  0, -1 }
};


int score()
{
    int ans = 0;
    for (int i = 0; i < 7; ++i)
        for (int j = 0; j < 7; ++j)
            if (board[i][j] == 'o')
                ans += sc_table[i][j];
    return ans;
}

bool valid(int r, int c)
{
    return r >= 0 && r < 7 && c >= 0 && c < 7;
}

int solve(int moves) {
    int best = score();
    if (moves == 0) return best;

    for (int i = 0; i < 7; ++i)
        for (int j = 0; j < 7; ++j)
            if (board[i][j] == 'o')
                for (int k = 0; k < 4; ++k) {
                    int r1 = i + dd[k][0];
                    int c1 = j + dd[k][1];
                    int r2 = r1 + dd[k][0];
                    int c2 = c1 + dd[k][1];

                    if (valid(r2, c2) && board[r1][c1] == 'o' &&
                        board[r2][c2] == '.') {

                        board[r1][c1] = board[i][j] = '.';
                        board[r2][c2] = 'o';
                        best = min(best, solve(moves - 1));
                        board[r1][c1] = board[i][j] = 'o';
                        board[r2][c2] = '.';
                    }
                }

    return best;
}

int main()
{
    int n;
    scanf("%d", &n);
    gets(board[0]);

    int ncase = 0;
    while (n--) {
        for (int i = 0; i < 7; ++i) gets(board[i]);

        printf("The best score for board #%d is %d points.\n",
               ++ncase, solve(10));
    }

    return 0;
}

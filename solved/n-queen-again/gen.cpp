#include <cstdio>
#include <cstdlib>
#include <ctime>


#define MAXT 200


char board[8][9];


void test_case()
{
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            board[i][j] = '.';

    for (int i = 0; i < 8; ++i) {
        int r, c;
        do {
            r = rand() % 8;
            c = rand() % 8;
        } while (board[r][c] != '.');
        board[r][c] = 'q';
    }

    puts("");
    for (int i = 0; i < 8; ++i)
        puts(board[i]);
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    while (T--) test_case();

    return 0;
}

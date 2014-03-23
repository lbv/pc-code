#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
using namespace std;


#define MAXT 100
#define MAX_DEPTH 35

#define Neg(v)  memset((v), -1, sizeof(v))


int puzzle[4][4];

const int dd[4][2] = {
    { -1,  0 },  // U
    {  0,  1 },  // R
    {  1,  0 },  // D
    {  0, -1 }   // L
};

void print_puzzle()
{
    putchar('\n');
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (j > 0) putchar(' ');
            printf("%d", puzzle[i][j]);
        }
        putchar('\n');
    }
}

void gen1()
{
    Neg(puzzle);
    for (int i = 0; i < 16; ++i) {
        int r, c;
        do {
            r = rand() % 4;
            c = rand() % 4;
        } while (puzzle[r][c] >= 0);
        puzzle[r][c] = i;
    }

    print_puzzle();
}

bool is_valid(int r, int c)
{
    return r >= 0 && r < 4 && c >= 0 && c < 4;
}

void gen2(bool crit = false)
{
    int n = 1;
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            puzzle[i][j] = n++;

    puzzle[3][3] = 0;
    int r = 3, c = 3;

    int moves = crit ? MAX_DEPTH : rand() % MAX_DEPTH + 1;
    int last_move = -1;

    while (moves--) {
        int new_move, r2, c2;
        do {
            new_move = rand() % 4;
            r2 = r + dd[new_move][0];
            c2 = c + dd[new_move][1];
        } while (new_move == (last_move + 2) % 4 || ! is_valid(r2, c2));
        swap(puzzle[r][c], puzzle[r2][c2]);
        r = r2, c = c2;
        last_move = new_move;
    }

    print_puzzle();
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    gen2(true); --T;
    while (T--) {
        if (rand() % 5 == 0)
            gen1();
        else
            gen2();
    }

    return 0;
}

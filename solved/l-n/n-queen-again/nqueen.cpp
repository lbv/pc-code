#include <cstdio>


#define GetFS(b) ((b) & -(b))
#define ClrFS(b) (b &= ~GetFS(b))

// values of (1 << x) for x<32 are unique modulo 37
static const int m37pos[] = {
    32,  0,  1, 26,  2, 23, 27,  0,  3,
    16, 24, 30, 28, 11,  0, 13,  4,  7,
    17,  0, 25, 22, 31, 15, 29, 10, 12,
     6,  0, 21, 14,  9,  5, 20,  8, 19, 18
};
#define Ctz(x) (m37pos[(x) % 37])

const int INF        = 100;
const int MAX_BOARDS = 40320;  // 8!, a gross overestimation


typedef unsigned int u32;


struct Pos {
    int r, c;
    Pos() {}
    Pos(int R, int C) : r(R), c(C) {}
};

struct Board {
    Pos q[8];
};


Board boards[MAX_BOARDS];
int   nboards;
int   ans;
int   moves[8][8];
Board b_input;


void find_boards(Board &board, int n, u32 col, u32 diag1, u32 diag2)
{
    if (n == 8) {
        boards[nboards++] = board;
        return;
    }

    for (int i = 0; i < 8; ++i) {
        int d1 = 7 - (n - i);
        int d2 = n + i;
        if (col & (1 << i) ||
            diag1 & (1 << d1) ||
            diag2 & (1 << d2))
            continue;
        board.q[n] = Pos(n, i);
        find_boards(board, n + 1, col | (1 << i),
                    diag1 | (1 << d1), diag2 | (1 << d2));
    }
}

void prepare()
{
    Board board;
    find_boards(board, 0, 0, 0, 0);
}

void read_board()
{
    char line[16];
    int n = 0;
    for (int i = 0; i < 8; ++i) {
        scanf("%s", line);
        for (int j = 0; j < 8; ++j)
            if (line[j] == 'q')
                b_input.q[n++] = Pos(i, j);
    }
}

int calc_moves(Pos &a, Pos &b)
{
    if (a.r == b.r && a.c == b.c) return 0;
    if (a.r == b.r || a.c == b.c) return 1;
    int d1a = 7 - (a.r - a.c);
    int d1b = 7 - (b.r - b.c);
    int d2a = a.r + a.c;
    int d2b = b.r + b.c;
    if (d1a == d1b || d2a == d2b) return 1;
    return 2;
}

void fill_moves(Board &target)
{
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
            moves[i][j] = calc_moves(b_input.q[i], target.q[j]);
}

void find_solution(int queen, int m, u32 bm)
{
    if (m >= ans) return;
    if (queen == 8) {
        ans = m;
        return;
    }
    for (u32 x = bm; x; ClrFS(x)) {
        u32 next = GetFS(x);
        int idx  = Ctz(next);

        find_solution(queen + 1, m + moves[queen][idx], bm & ~next);
    }
}

void print_board(Board &board)
{
    char b[8][9];
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j)
            b[i][j] = '.';
        b[i][8] = 0;
    }

    for (int i = 0; i < 8; ++i) {
        Pos &p = board.q[i];
        b[p.r][p.c] = 'q';
    }
    for (int i = 0; i < 8; ++i)
        puts(b[i]);
}

void solve()
{
    ans = INF;
    for (int i = 0; i < nboards; ++i) {
        fill_moves(boards[i]);
        find_solution(0, 0, (1 << 8) - 1);
    }
}

int main()
{
    prepare();

    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        read_board();
        solve();
        printf("Case %d: %d\n", ++ncase, ans);
    }

    return 0;
}

#include <cstdio>
#include <cstring>


#define MAXM 50
#define MAXN 50

#define Zero(v) memset((v), 0, sizeof(v))

const int MAX_QUEUE = MAXM * MAXN;


struct Pos {
    int r, c;
    Pos() {}
    Pos(int R, int C) : r(R), c(C) {}
};


int  m, n;
char grid[MAXM][MAXN + 1];
bool aux[MAXM][MAXN + 1];

bool used[26];

Pos q[MAX_QUEUE];
int front, back;

const int dd[4][2] = {
    { -1,  0 },
    {  1,  0 },
    {  0, -1 },
    {  0,  1 }
};


void enqueue(int r, int c)
{
    q[++front] = Pos(r, c);
    aux[r][c] = true;
}

bool valid(int r, int c)
{
    return r >= 0 && r < m && c >= 0 && c < n;
}

void fill(char l)
{
    Zero(aux);
    front = -1, back = 0;

    for (int r = 0; r < m; ++r) {
        if (grid[r][0] != l) enqueue(r, 0);
        if (grid[r][n-1] != l) enqueue(r, n-1);
    }
    for (int c = 1, C = n - 1; c < C; ++c) {
        if (grid[0][c] != l) enqueue(0, c);
        if (grid[m-1][c] != l) enqueue(m-1, c);
    }

    while (back <= front) {
        Pos &p = q[back++];

        for (int i = 0; i < 4; ++i) {
            int r = p.r + dd[i][0], c = p.c + dd[i][1];
            if (valid(r, c) && ! aux[r][c] && grid[r][c] != l)
                enqueue(r, c);
        }
    }

    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            if (! aux[i][j]) grid[i][j] = l;
}

void solve()
{
    Zero(used);

    for (int r = 0; r < m; ++r)
        for (int c = 0; c < n; ++c) {
            char &l = grid[r][c];
            int idx = l - 'A';
            if (l != '.' && ! used[idx]) {
                fill(l);
                used[idx] = true;
            }
        }
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d", &m, &n);
        for (int i = 0; i < m; ++i) scanf("%s", grid[i]);

        solve();
        printf("Case %d:\n", ++ncase);
        for (int i = 0; i < m; ++i) printf("%s\n", grid[i]);
    }

    return 0;
}

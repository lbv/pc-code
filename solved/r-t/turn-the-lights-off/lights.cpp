#include <cstdio>
#include <cstring>

#define MAXNAME 1024

typedef unsigned int u32;

char name[MAXNAME];
char line[11];
bool grid[10][10];
bool aux[10][10];

const bool end[10][10] = { { 0 } };
const int dd[4][2] = {
    { -1,  0 },
    {  1,  0 },
    {  0, -1 },
    {  0,  1 }
};

int moves;

void read_grid()
{
    for (int i = 0; i < 10; ++i) {
        scanf("%s", line);
        for (int j = 0; j < 10; ++j)
            grid[i][j] = line[j] == 'O';
    }
}

bool is_valid(int r, int c)
{
    return r >= 0 && r < 10 && c >= 0 && c < 10;
}

void flip(int i, int j)
{
    ++moves;

    aux[i][j] = !aux[i][j];
    for (int k = 0; k < 4; ++k) {
        int r = i + dd[k][0];
        int c = j + dd[k][1];

        if (is_valid(r, c))
            aux[r][c] = !aux[r][c];
    }
}

int solve()
{
    u32 top = 1 << 10;
    for (u32 opt = 0; opt < top; ++opt) {
        memcpy(aux, grid, sizeof(grid));

        moves = 0;

        for (int j = 0; j < 10; ++j)
            if (opt & (1 << j))
                flip(0, j);

        for (int i = 1; i < 10; ++i)
            for (int j = 0; j < 10; ++j)
                if (aux[i - 1][j])
                    flip(i, j);

        if (memcmp(end, aux, sizeof(aux)) == 0)
            return moves;
    }
    return -1;
}

int main()
{
    while (true) {
        scanf("%s", name);
        if (strcmp(name, "end") == 0) break;

        read_grid();
        printf("%s %d\n", name, solve());
    }

    return 0;
}

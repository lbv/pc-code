#include <cstdio>
#include <cstring>


#define Neg(v)  memset((v), -1, sizeof(v))


typedef unsigned int u32;


u32 grid;
int memo[1 << 9];


#define Cell(m,i) ( ((m) & (1 << i)) ? 1 : 0 )
u32 f(u32 g)
{
    u32 r = 0;
    if (Cell(g, 1) ^ Cell(g, 3)) r |= 1 << 0;
    if (Cell(g, 0) ^ Cell(g, 2) ^ Cell(g, 4)) r |= 1 << 1;
    if (Cell(g, 1) ^ Cell(g, 5)) r |= 1 << 2;
    if (Cell(g, 0) ^ Cell(g, 4) ^ Cell(g, 6)) r |= 1 << 3;
    if (Cell(g, 1) ^ Cell(g, 3) ^ Cell(g, 5) ^ Cell(g, 7)) r |= 1 << 4;
    if (Cell(g, 2) ^ Cell(g, 4) ^ Cell(g, 8)) r |= 1 << 5;
    if (Cell(g, 3) ^ Cell(g, 7)) r |= 1 << 6;
    if (Cell(g, 6) ^ Cell(g, 4) ^ Cell(g, 8)) r |= 1 << 7;
    if (Cell(g, 5) ^ Cell(g, 7)) r |= 1 << 8;
    return r;
}

int k(u32 g)
{
    if (g == 0) return 0;
    if (memo[g] >= 0) return memo[g];

    int val = 1 + k(f(g));

    return memo[g] = val;
}

int main()
{
    int T;
    scanf("%d", &T);

    Neg(memo);

    while (T--) {
        grid = 0;
        for (int i = 0; i < 9; ++i) {
            char c;
            scanf(" %c", &c);
            if (c == '1')
                grid |= 1 << i;
        }

        printf("%d\n", k(grid) - 1);
    }

    return 0;
}

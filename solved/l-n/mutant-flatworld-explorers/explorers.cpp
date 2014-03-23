#include <cstdio>
#include <cstring>


#define MAXX 50
#define MAXY 50
#define MAXLEN 100

#define Zero(v) memset((v), 0, sizeof(v))


int X, Y;
char ins[MAXLEN + 1];

int x, y, d;

bool scent[MAXX + 1][MAXY + 1];
const char dirs_str[] = "NESW";
const int dirs[4][2] = {
    {  0,  1 },
    {  1,  0 },
    {  0, -1 },
    { -1,  0 }
};


void simulate()
{
    int n = strlen(ins);
    int x2, y2;

    bool lost = false;
    for (int i = 0; i < n; ++i) {
        if (ins[i] == 'L') {
            d = (d + 3) % 4;
            continue;
        }
        else if (ins[i] == 'R') {
            d = (d + 1) % 4;
            continue;
        }
        else if (ins[i] != 'F') continue;

        x2 = x + dirs[d][0];
        y2 = y + dirs[d][1];

        if (x2 >= 0 && x2 <= X && y2 >= 0 && y2 <= Y) {
            x = x2, y = y2;
            continue;
        }

        if (scent[x][y]) continue;
        scent[x][y] = true;
        lost = true;
        break;
    }

    printf("%d %d %c", x, y, dirs_str[d]);
    if (lost) puts(" LOST");
    else putchar('\n');
}

int main()
{
    scanf("%d%d", &X, &Y);
    char o[4];
    while (true) {
        if (scanf("%d%d%s%s", &x, &y, o, ins) != 4) break;

        d = strcspn(dirs_str, o);
        simulate();
    }

    return 0;
}

#include <cstdio>
#include <cstring>

#define MAXS 512

#define Zero(v) memset(v, 0, sizeof(v))

int b, w;
char maze[MAXS][MAXS];
int cnt[MAXS][MAXS];
int ans[5];

const int dd[4][2] = {
    {  0,  1 },  // East
    { -1,  0 },  // North
    {  0, -1 },  // West
    {  1,  0 }   // South
};

bool valid_pos(int r, int c)
{
    return r >= 0 && r < b && c >= 0 && c < w;
}

bool can_move(int r, int c, int dir)
{
    int r2 = r + dd[dir][0];
    int c2 = c + dd[dir][1];

    return valid_pos(r2, c2) && maze[r2][c2] == '0';
}

int move_left(int dir)
{
    return (dir + 1) % 4;
}

int move_right(int dir)
{
    return dir == 0 ? 3 : dir - 1;
}

bool wall_right(int r, int c, int dir)
{
    int d2 = move_right(dir);
    int r2 = r + dd[d2][0];
    int c2 = c + dd[d2][1];

    return (!valid_pos(r2, c2)) || maze[r2][c2] == '1';
}

void solve()
{
    Zero(ans);
    Zero(cnt);

    int r = b - 1;
    int c = 0;
    int dir = 0;

    for (int i = 0; i < b; ++i)
        for (int j = 0; j < w; ++j)
            if (maze[i][j] == '0') ++ans[0];

    while (true) {
        while (! can_move(r, c, dir))
            dir = move_left(dir);

        r += dd[dir][0];
        c += dd[dir][1];

        if (cnt[r][c] <= 4) --ans[cnt[r][c]];
        ++cnt[r][c];
        if (cnt[r][c] <= 4) ++ans[cnt[r][c]];

        if (r == b - 1 && c == 0) break;

        if (! wall_right(r, c, dir))
            dir = move_right(dir);
    }
}

int main()
{
    while (true) {
        scanf("%d%d", &b, &w);
        if (b == 0 && w == 0) break;

        for (int i = 0; i < b; ++i) scanf("%s", maze[i]);

        solve();
        printf("%3d%3d%3d%3d%3d\n", ans[0], ans[1], ans[2], ans[3], ans[4]);
    }

    return 0;
}

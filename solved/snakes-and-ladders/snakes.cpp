#include <cstdio>
#include <cstring>

#define MAXPLAYERS 1000000
#define BOARD 100

#define Zero(v) memset(v, 0, sizeof(v))

int players[MAXPLAYERS];
int cfg[BOARD + 1];  // has the snakes and ladders info
int a, b, c;
int die;
int cur;  // current player

bool fin;  // has game finished?

void init_game()
{
    fin = false;
    cur = 0;
    for (int i = 0; i < a; ++i)
        players[i] = 1;

    for (int p = 1; p < 100; ++p)
        if (cfg[p] != 0) {
            int x = p;
            while (cfg[x] != 0)
                x = cfg[x];
            cfg[p] = x;
        }
}

void move()
{
    if (fin) return;
    players[cur] += die;

    if (players[cur] < 100 && cfg[players[cur]] != 0)
        players[cur] = cfg[players[cur]];

    if (players[cur] >= 100) {
        players[cur] = 100;
        fin = true;
    }

    cur = (cur + 1) % a;
}

int main()
{
    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%d%d%d", &a, &b, &c);

        Zero(cfg);

        while (b--) {
            int x, y;
            scanf("%d%d", &x, &y);
            cfg[x] = y;
        }

        init_game();

        while (c--) {
            scanf("%d", &die);
            move();
        }

        for (int i = 0; i < a; ++i)
            printf("Position of player %d is %d.\n", i + 1, players[i]);
    }

    return 0;
}

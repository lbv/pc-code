#include <cstdio>
#include <cstring>

#define Zero(v) memset(v, 0, sizeof(v))

// I/O
#define BUF 65536
struct Reader {
    char buf[BUF]; char b; int bi, bz;
    Reader() { bi=bz=0; read(); }
    void read() {
        if (bi==bz) { bi=0; bz = fread(buf, 1, BUF, stdin); }
        b = bz ? buf[bi++] : 0; }
    void skip() { while (b > 0 && b <= 32) read(); }
    void next_line(char *s) {
        for (; b != 10 && b != 13 && b != 0; read()) *s++ = b; *s = 0;
        while (b == 10 || b == 13) read(); }
};

char game[4*12 + 1];

int roll[25];  // score of each roll
char bon[13];  // bonuses attached to each roll

int score()
{
    Zero(roll);
    int len = strlen(game);

    for (int i = 0, r = 1; r <= 24 && i < len; ++r, i += 2) {
        if (game[i] == 'X') {
            roll[r] = 10;
            bon[r] = 'X';
        }
        else if (game[i] == '/') {
            roll[r] = 10 - roll[r - 1];
            bon[r] = '/';
        }
        else {
            roll[r] = game[i] - '0';
            bon[r] = ' ';
        }
    }

    int ans = 0;
    int r = 1;
    for (int f = 1; f <= 10; ++f) {
        ans += roll[r];

        if (bon[r] == 'X')
            ans += roll[r + 1] + roll[r + 2];
        else if (bon[r] == ' ') {
            ++r;
            ans += roll[r];

            if (bon[r] == '/')
                ans += roll[r + 1];
        }

        ++r;
    }

    return ans;
}

int main()
{
    Reader rr;

    while (true) {
        rr.next_line(game);
        if (game[0] == 'G') break;

        printf("%d\n", score());
    }

    return 0;
}

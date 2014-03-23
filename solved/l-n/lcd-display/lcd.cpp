#include <cmath>
#include <cstdio>
#include <cstring>


#define MAXS 10
#define MAXD 8   // maximum number of digits

#define LINE1 (1 << 0)
#define LINE2 (1 << 1)
#define LINE3 (1 << 2)
#define LINE4 (1 << 3)
#define LINE5 (1 << 4)
#define LINE6 (1 << 5)
#define LINE7 (1 << 6)


const int MAXROWS = 2*MAXS + 3;
const int MAXCOLS = (MAXS + 3) * MAXD;

const int digits[10] = {
    LINE1 | LINE2 | LINE3 |         LINE5 | LINE6 | LINE7,  // 0
                    LINE3 |                 LINE6        ,  // 1
    LINE1 |         LINE3 | LINE4 | LINE5 |         LINE7,  // 2
    LINE1 |         LINE3 | LINE4 |         LINE6 | LINE7,  // 3
            LINE2 | LINE3 | LINE4 |         LINE6        ,  // 4
    LINE1 | LINE2 |         LINE4 |         LINE6 | LINE7,  // 5
    LINE1 | LINE2 |         LINE4 | LINE5 | LINE6 | LINE7,  // 6
    LINE1 |         LINE3 |                 LINE6        ,  // 7
    LINE1 | LINE2 | LINE3 | LINE4 | LINE5 | LINE6 | LINE7,  // 8
    LINE1 | LINE2 | LINE3 | LINE4 |         LINE6 | LINE7   // 9
};

char lcd[MAXROWS][MAXCOLS + 1];
int s, n;
int H, W;  // height and width of the current number
int D;     // number of digits in the current number


void draw_digit(int d, int pos)
{
    int col = (s + 3) * pos;

    if (digits[d] & LINE1)
        for (int j = col + 1, x = 0; x < s; ++x, ++j)
            lcd[0][j] = '-';
    if (digits[d] & LINE4) {
        int r = s + 1;
        for (int j = col + 1, x = 0; x < s; ++x, ++j)
            lcd[r][j] = '-';
    }
    if (digits[d] & LINE7) {
        int r = H - 1;
        for (int j = col + 1, x = 0; x < s; ++x, ++j)
            lcd[r][j] = '-';
    }
    if (digits[d] & LINE2)
        for (int i = 1; i <= s; ++i)
            lcd[i][col] = '|';
    if (digits[d] & LINE3) {
        int c = col + s + 1;
        for (int i = 1; i <= s; ++i)
            lcd[i][c] = '|';
    }
    if (digits[d] & LINE5) {
        int c = col;
        for (int i = s + 2, x = 0; x < s; ++x, ++i)
            lcd[i][c] = '|';
    }
    if (digits[d] & LINE6) {
        int c = col + s + 1;
        for (int i = s + 2, x = 0; x < s; ++x, ++i)
            lcd[i][c] = '|';
    }
}

void build_lcd()
{
    D = n == 0 ? 1 : 1 + log10(n);

    H = 2*s + 3;
    W = (s + 3) * D;

    memset(lcd, ' ', sizeof(lcd));
    for (int i = 0; i < H; ++i)
        lcd[i][W - 1] = 0;

    for (int d = D - 1; d >= 0; --d) {
        int dig = n % 10;
        n /= 10;

        draw_digit(dig, d);
    }
}

void print_lcd()
{
    for (int i = 0; i < H; ++i)
        printf("%s\n", lcd[i]);
    putchar('\n');
}

int main()
{
    while (true) {
        scanf("%d%d", &s, &n);
        if (s == 0 && n == 0) break;

        build_lcd();
        print_lcd();
    }

    return 0;
}

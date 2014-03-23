#include <cstdio>


#define MAXN 100

#define R_I 0
#define R_V 1
#define R_X 2
#define R_L 3
#define R_C 4


int N;
int rom[5];
int acc[MAXN + 1][5];


void solve(int n)
{
    rom[0] = rom[1] = rom[2] = rom[3] = rom[4] = 0;

    if (n >= 100) {
        ++rom[R_C];
        n -= 100;
    }

    if (n >= 90) {
        ++rom[R_X];
        ++rom[R_C];
        n -= 90;
    }

    if (n >= 50) {
        ++rom[R_L];
        n -= 50;
    }

    if (n >= 40) {
        ++rom[R_X];
        ++rom[R_L];
        n -= 40;
    }

    while (n >= 10) {
        ++rom[R_X];
        n -= 10;
    }

    if (n >= 9) {
        ++rom[R_I];
        ++rom[R_X];
        n -= 9;
    }

    if (n >= 5) {
        ++rom[R_V];
        n -= 5;
    }

    if (n >= 4) {
        ++rom[R_I];
        ++rom[R_V];
        n -= 4;
    }

    while (n >= 1) {
        ++rom[R_I];
        --n;
    }
}

void prepare()
{
    for (int i = 1; i <= MAXN; ++i) {
        solve(i);
        for (int j = 0; j < 5; ++j)
            acc[i][j] = acc[i - 1][j] + rom[j];
    }
}

int main()
{
    prepare();

    while (true) {
        scanf("%d", &N);
        if (N == 0) break;

        printf("%d: %d i, %d v, %d x, %d l, %d c\n", N,
               acc[N][0], acc[N][1], acc[N][2], acc[N][3], acc[N][4]);
    }

    return 0;
}

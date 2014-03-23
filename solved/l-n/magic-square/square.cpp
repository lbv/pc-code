#include <cmath>
#include <cstdio>
#include <cstring>


#define MAXN 15

#define Zero(v) memset((v), 0, sizeof(v))


int sq[MAXN][MAXN];
int n, sum;

const char fmts[3][8] = {
    " %1d",
    " %2d",
    " %3d"
};


void solve()
{
    Zero(sq);

    int r = 0, c = n / 2;
    for (int i = 1, I = n*n; i <= I; ++i) {
        sq[r][c] = i;

        int r2 = (r - 1 + n) % n;
        int c2 = (c + 1) % n;

        if (sq[r2][c2] == 0) r = r2, c = c2;
        else r = (r + 1) % n;
    }

    sum = 0;
    for (int i = 0; i < n; ++i) sum += sq[0][i];
}

void print_square()
{
    int len = 1 + log10(n*n);

    const char *f = fmts[len - 1];

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            printf(f, sq[i][j]);
        putchar('\n');
    }
}

int main()
{
    bool first = true;
    while (true) {
        if (scanf("%d", &n) != 1) break;
        solve();

        if (first) first = false;
        else putchar('\n');

        printf("n=%d, sum=%d\n", n, sum);
        print_square();
    }

    return 0;
}

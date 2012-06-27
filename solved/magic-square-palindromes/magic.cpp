#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstring>

#define MAXLEN 10000
#define MAXSQ  100

typedef unsigned int u32;

// I/O
#define BUF 65536
struct Reader {
    char buf[BUF]; char b; int bi, bz;
    Reader() { bi=bz=0; read(); }
    void read() {
        if (bi==bz) { bi=0; bz = fread(buf, 1, BUF, stdin); }
        b = bz ? buf[bi++] : 0; }
    void skip() { while (b > 0 && b <= 32) read(); }
    u32 next_u32() {
        u32 v = 0; for (skip(); b > 32; read()) v = v*10 + b-48; return v; }
    void next_line(char *s, int &l) {
        for (l=0; b != 10 && b != 13 && b != 0; read()) *s++ = b, ++l; *s = 0;
        while (b == 10 || b == 13) read(); }
};

char line[MAXLEN + 1];
char str[MAXLEN + 1];
char square[MAXSQ][MAXSQ];
int len, n, K;

bool solve()
{
    K = sqrt(n);
    if (K*K != n) return false;

    for (int i = 0; i < n; ++i)
        square[i / K][i % K] = str[i];

    int a, b, c, d;

    // left to right, top to bottom
    a = b = 0;
    c = d = K - 1;
    for (int i = 0, j = n - 1; i < j; ++i, --j) {
        if (square[a][b] != square[c][d]) return false;
        ++b;
        if (b == K) b = 0, ++a;

        --d;
        if (d < 0) d = K - 1, --c;
    }

    // top to bottom, left to right
    a = b = 0;
    c = d = K - 1;
    for (int i = 0, j = n - 1; i < j; ++i, --j) {
        if (square[a][b] != square[c][d]) return false;
        ++a;
        if (a == K) a = 0, ++b;

        --c;
        if (c < 0) c = K - 1, --d;
    }

    return true;
}

int main()
{
    Reader rr;
    int T = rr.next_u32();
    rr.next_line(line, len);

    int ncase = 0;
    while (T--) {
        rr.next_line(line, len);

        n = 0;
        for (int i = 0; i < len; ++i)
            if (islower(line[i]))
                str[n++] = line[i];

        printf("Case #%d:\n", ++ncase);

        if (solve())
            printf("%d\n", K);
        else
            puts("No magic :(");
    }

    return 0;
}

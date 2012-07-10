#include <cstdio>

#define MAXLEN 128

typedef unsigned int u32;

//
// I/O
//
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
    void next_real_line(char *s, int &l) {
        for (l = 0; b != 10 && b != 13 && b != 0; read()) *s++ = b, ++l;
        *s = 0; char p = b; read();
        if ((p == 10 && b == 13) || (p == 13 && b == 10)) read(); }
};

char str[MAXLEN + 1];
char stk[MAXLEN];
int len;

bool well_formed()
{
    int sz = 0;

    for (int i = 0; i < len; ++i) {
        if (str[i] == '[' || str[i] == '(')
            stk[sz++] = str[i];
        else {
            if (sz == 0) return false;
            char top = stk[--sz];

            if (str[i] == ']' && top != '[') return false;
            if (str[i] == ')' && top != '(') return false;
        }
    }

    return sz == 0;
}

int main()
{
    Reader rr;

    int n = rr.next_u32();
    rr.next_real_line(str, len);

    while (n--) {
        rr.next_real_line(str, len);

        if (well_formed()) puts("Yes");
        else puts("No");
    }

    return 0;
}

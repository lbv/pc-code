#include <cstdio>
#include <cstring>

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
    u32 nextU32() {
        u32 v = 0; for (skip(); b > 32; read()) v = v*10 + b-48; return v; }
    void next(char *s) { for (skip(); b > 32; read()) *s++ = b; *s = 0; }
};

char n[80];

bool palindrome()
{
    char *i = n;
    char *j = i + strlen(n) - 1;
    while (i <= j) {
        if (*i != *j) return false;
        ++i; --j;
    }
    return true;
}

int main()
{
    Reader rr;
    u32 T = rr.nextU32();

    int ncase = 1;
    while (T--) {
        rr.next(n);
        if (palindrome())
            printf("Case %d: Yes\n", ncase++);
        else
            printf("Case %d: No\n", ncase++);
    }

    return 0;
}

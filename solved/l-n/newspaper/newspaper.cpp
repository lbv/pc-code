#include <cstdio>
#include <cstring>

#define MAXLEN 10000

#define Sc(t,v) static_cast<t>(v)
#define Zero(v) memset(v, 0, sizeof(v))

typedef unsigned char      uc;
typedef unsigned int       u32;
typedef unsigned long long u64;

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
    char next_char() { skip(); char c = b; read(); return c; }
    void next_real_line(char *s, int &l) {
        for (l = 0; b != 10 && b != 13 && b != 0; read()) *s++ = b, ++l;
        *s = 0; char p = b; read();
        if ((p == 10 && b == 13) || (p == 13 && b == 10)) read(); }
};

int table[256];
char line[MAXLEN + 1];
int len;

int main()
{
    Reader rr;
    int N = rr.next_u32();

    while (N--) {
        int K = rr.next_u32();

        Zero(table);
        while (K--) {
            char c = rr.next_char();
            table[Sc(uc, c)] = rr.next_u32();
        }

        int M = rr.next_u32();
        rr.next_real_line(line, len);

        u64 total = 0;

        while (M--) {
            rr.next_real_line(line, len);
            for (int i = 0; i < len; ++i)
                total += table[Sc(uc, line[i])];
        }

        printf("%llu.%02llu$\n", total / 100, total % 100);
    }

    return 0;
}

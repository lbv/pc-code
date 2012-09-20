#include <cstdio>
#include <cstring>


#define MAXN 100000

#define Zero(v) memset((v), 0, sizeof(v))
#define Back(b) ((b) & -(b))


typedef unsigned int u32;


//
// I/O
//
#define BUF 524288
struct Reader {
    char buf[BUF]; char b; int bi, bz;
    Reader() { bi=bz=0; read(); }
    void read() {
        if (bi==bz) { bi=0; bz = fread(buf, 1, BUF, stdin); }
        b = bz ? buf[bi++] : 0; }
    void skip() { while (b > 0 && b <= 32) read(); }
    u32 next_u32() {
        u32 v = 0; for (skip(); b > 32; read()) v = v*10 + b-48; return v; }
    void next(char *s, int &l) {
        l = 0; for (skip(); b > 32; read()) *s++ = b, ++l; *s = 0; }
    char next_char() { skip(); char c = b; read(); return c; }
};


//
// Binary Indexed Tree
//
const int BitMax = MAXN;
struct Bit {
    int f[BitMax + 1];
    Bit() { Zero (f); }
    void add(int i, int v) { while (i <= BitMax) { f[i] += v; i += Back(i); } }
    int query(int i) {
        int r = 0; while (i) { r += f[i]; i -= Back(i); } return r; }
};


int n, q;
char seq[MAXN + 1];


void init_bit(Bit &t)
{
    for (int i = 1; i <= n; ++i)
        if (seq[i - 1] == '1') {
            t.add(i, 1);
            if (i < n)
                t.add(i + 1, 1);
        }
}

int main()
{
    Reader rr;

    int T = rr.next_u32();

    int ncase = 0;
    while (T--) {
        printf("Case %d:\n", ++ncase);

        rr.next(seq, n);

        Bit tree;
        init_bit(tree);

        q = rr.next_u32();

        while (q--) {
            char type = rr.next_char();

            if (type == 'I') {
                int i = rr.next_u32();
                int j = rr.next_u32();

                tree.add(i, 1);
                if (j < n)
                    tree.add(j + 1, 1);
            }
            else {
                int i = rr.next_u32();

                int cnt = tree.query(i);
                printf("%d\n", cnt & 1);
            }
        }
    }

    return 0;
}

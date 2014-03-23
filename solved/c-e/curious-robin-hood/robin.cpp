#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;


#define MAXN 100000

#define Zero(v) memset((v), 0, sizeof(v))
#define Back(b)    ((b) & -(b))


typedef unsigned int u32;

typedef vector<int> IV;


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
};

//
// Binary Indexed Tree
//
struct Bit {
    IV f; int n;
    Bit(int N) : n(N) { f = IV(N + 1); }
    void add(int i, int v) { while (i <= n) { f[i] += v; i += Back(i); } }
    int query(int i) {
        int r = 0; while (i) { r += f[i]; i -= Back(i); } return r; }
};


int n, q;


int main()
{
    Reader rr;
    int T = rr.next_u32();

    int ncase = 0;
    while (T--) {
        n = rr.next_u32();
        q = rr.next_u32();

        printf("Case %d:\n", ++ncase);

        Bit tree(n);

        for (int i = 1; i <= n; ++i) {
            int v = rr.next_u32();
            if (v > 0)
                tree.add(i, v);
        }

        while (q--) {
            int type = rr.next_u32();

            if (type == 1) {
                int i = rr.next_u32();
                ++i;

                int v = tree.query(i) - tree.query(i - 1);
                printf("%d\n", v);
                tree.add(i, -v);
            }
            else if (type == 2) {
                int i = rr.next_u32();
                int v = rr.next_u32();
                ++i;

                tree.add(i, v);
            }
            else {
                int i = rr.next_u32();
                int j = rr.next_u32();
                ++i; ++j;

                int v = tree.query(j) - tree.query(i - 1);
                printf("%d\n", v);
            }
        }
    }

    return 0;
}

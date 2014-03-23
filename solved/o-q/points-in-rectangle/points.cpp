#include <cstdio>
#include <cstring>


#define MAXCOORD 1000

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
};

//
// Binary Indexed Tree
//
const int BitMax = MAXCOORD + 1;
struct Bit {
    int f[BitMax + 1];
    Bit() { Zero (f); }
    void add(int i, int v) { while (i <= BitMax) { f[i] += v; i += Back(i); } }
    int query(int i) {
        int r = 0; while (i) { r += f[i]; i -= Back(i); } return r; }
};
struct Bit2d {
    Bit g[BitMax + 1];
    void add(int x, int y, int v) {
        while (x <= BitMax) {
            g[x].add(y, v);
            x += Back(x);
        }
    }
    int query(int x, int y) {
        if (x == 0 || y == 0) return 0;
        int r = 0;
        while (x) {
            r += g[x].query(y);
            x -= Back(x);
        }
        return r;
    }
};


int q, type;
int x1, y1, x2, y2;

bool points[MAXCOORD + 2][MAXCOORD + 2];


int main()
{
    Reader rr;

    int T = rr.next_u32();;

    int ncase = 0;
    while (T--) {
        q = rr.next_u32();
        printf("Case %d:\n", ++ncase);

        Zero(points);

        Bit2d tree;

        while (q--) {
            type = rr.next_u32();

            if (type == 0) {
                x1 = rr.next_u32();
                y1 = rr.next_u32();

                ++x1; ++y1;

                if (points[x1][y1]) continue;

                tree.add(x1, y1, 1);
                points[x1][y1] = true;
            }
            else {
                x1 = rr.next_u32();
                y1 = rr.next_u32();
                x2 = rr.next_u32();
                y2 = rr.next_u32();

                ++x1; ++y1; ++x2; ++y2;

                int ans = tree.query(x2, y2) - tree.query(x1 - 1, y2) -
                    tree.query(x2, y1 - 1) + tree.query(x1 - 1, y1 - 1);

                printf("%d\n", ans);
            }
        }
    }

    return 0;
}

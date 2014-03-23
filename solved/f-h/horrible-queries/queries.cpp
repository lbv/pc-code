#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;


#define MAXN 100000

#define Zero(v) memset((v), 0, sizeof(v))


typedef unsigned int u32;
typedef long long i64;


struct Reader {
    char b; Reader() { read(); }
    void read() { int r = fgetc_unlocked(stdin); b = r == EOF ? 0 : r; }
    void skip() { while (b > 0 && b <= 32) read(); }

    u32 next_u32() {
        u32 v = 0; for (skip(); b > 32; read()) v = v*10 + b-48; return v; }
};

#define MAXH 18  // 1 + ceil(log2(MAXN))
struct SegTree {
    i64 T[1 << MAXH];
    i64 U[1 << MAXH];
    int n;
    void init(int N) { n = N; Zero(T); Zero(U); }

    void propagate(int x, int a, int b) {
        if (U[x] == 0) return;
        T[x] += U[x] * (b - a + 1);
        if (a != b) {
            int lt = 2*x, rt = lt + 1;
            U[lt] += U[x];
            U[rt] += U[x];
        }
        U[x] = 0;
    }

    void update(int i, int j, i64 v) { tree_update(i, j, v, 1, 0, n-1); }
    void tree_update(int i, int j, i64 v, int x, int a, int b) {
        propagate(x, a, b);
        if (j < a || i > b) return;
        if (a == b) { T[x] += v; return; }
        int lt = 2*x, rt = lt + 1, md = (a+b)/2;
        if (a >= i && b <= j) {
            T[x] += v * (b - a + 1);
            U[lt] += v;
            U[rt] += v;
            return;
        }
        tree_update(i, j, v, lt, a, md);
        tree_update(i, j, v, rt, md + 1, b);
        T[x] = T[rt] + T[lt];
    }

    i64 query(int i, int j) { return tree_query(i, j, 1, 0, n-1); }
    i64 tree_query(int i, int j, int x, int a, int b) {
        if (j < a || i > b) return -1;
        propagate(x, a, b);
        if (a >= i && b <= j) return T[x];
        int lt = 2*x, rt = lt + 1, md = (a+b)/2;
        i64 q1 = tree_query(i, j, lt, a, md);
        i64 q2 = tree_query(i, j, rt, md + 1, b);
        if (q1 < 0) return q2;
        if (q2 < 0) return q1;
        return q1 + q2;
    }
};



int n, q;
SegTree tree;


int main()
{
    Reader rr;
    int T = rr.next_u32();

    int ncase = 0;
    while (T--) {
        n = rr.next_u32();
        q = rr.next_u32();

        tree.init(n);
        printf("Case %d:\n", ++ncase);

        while (q--) {
            int type = rr.next_u32();

            if (type == 0) {
                int x = rr.next_u32();
                int y = rr.next_u32();
                int v = rr.next_u32();

                tree.update(x, y, v);
            }
            else {
                int x = rr.next_u32();
                int y = rr.next_u32();
                printf("%lld\n", tree.query(x, y));
            }
        }
    }

    return 0;
}

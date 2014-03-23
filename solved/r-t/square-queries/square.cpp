#include <algorithm>
#include <cstdio>
using namespace std;


#define MAXN 500


typedef unsigned int u32;


struct Reader {
    int b; Reader() { read(); }
    void read() { b = getchar_unlocked(); }
    void skip() { while (b >= 0 && b <= 32) read(); }

    u32 next_u32() {
        u32 v = 0; for (skip(); b > 32; read()) v = 10*v+b-48; return v; }
};

//
// R-Tree for 2D matrices
//
const int MAX_ROWS = MAXN;
const int MAX_COLS = MAXN;
const int MAX_H    = 19;   // 1 + ceil(log2(MAX_ROWS * MAX_COLS))
template <typename NT>
struct R2Tree {
    struct Node { NT v; };

    Node T[1 << MAX_H];
    NT   M[MAX_ROWS][MAX_COLS];
    int  r, c;

    void init(int R, int C) { tree_init(1, 0, 0, r=R, c=C, 0); }
    void tree_init(int x, int r1, int c1, int r2, int c2, int o) {
        if (r1 == r2 && c1 == c2) {
            T[x].v = M[r1][c1];
            return;
        }

        int op = (o + 1) % 2;
        int lt = 2*x, rt = lt + 1;
        if ((o == 0 && c1 < c2) || r1 == r2) {
            int md = (c1 + c2) / 2;
            tree_init(lt, r1, c1, r2, md, op);
            tree_init(rt, r1, md + 1, r2, c2, op);
        }
        else {
            int md = (r1 + r2) / 2;
            tree_init(lt, r1, c1, md, c2, op);
            tree_init(rt, md + 1, c1, r2, c2, op);
        }
        T[x].v = max(T[lt].v, T[rt].v);
    }

    int qr1, qc1, qr2, qc2;
    NT get(int r1, int c1, int r2, int c2) {
        qr1 = r1, qc1 = c1, qr2 = r2, qc2 = c2;
        return tree_get(1, 0, 0, r, c, 0);
    }
    NT tree_get(int x, int r1, int c1, int r2, int c2, int o) {
        if (r1 >= qr1 && r2 <= qr2 && c1 >= qc1 && c2 <= qc2) return T[x].v;
        if (r1 > qr2 || r2 < qr1 || c1 > qc2 || c2 < qc1) return -1;

        int op = (o + 1) % 2;
        int lt = 2*x, rt = lt + 1;
        NT a, b;
        if ((o == 0 && c1 < c2) || r1 == r2) {
            int md = (c1 + c2) / 2;
            a = tree_get(lt, r1, c1, r2, md, op);
            b = tree_get(rt, r1, md + 1, r2, c2, op);
        }
        else {
            int md = (r1 + r2) / 2;
            a = tree_get(lt, r1, c1, md, c2, op);
            b = tree_get(rt, md + 1, c1, r2, c2, op);
        }
        return max(a, b);
    }
};


int N, Q;
R2Tree<int> tree;


int main()
{
    Reader rr;
    int T = rr.next_u32();

    int ncase = 0;
    while (T--) {
        N = rr.next_u32();
        Q = rr.next_u32();

        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                tree.M[i][j] = rr.next_u32();

        tree.init(N, N);

        printf("Case %d:\n", ++ncase);
        while (Q--) {
            int I = rr.next_u32();
            int J = rr.next_u32();
            int S = rr.next_u32();
            printf("%d\n", tree.get(I - 1, J - 1, I + S - 2, J + S - 2));
        }
    }

    return 0;
}

#include <cstdio>
#include <cstring>


#define Zero(v) memset((v), 0, sizeof(v))


typedef unsigned int u32;


struct Reader {
    int b; Reader() { read(); }
    void read() { b = getchar_unlocked(); }
    void skip() { while (b >= 0 && b <= 32) read(); }

    u32 next_u32() {
        u32 v = 0; for (skip(); b > 32; read()) v = 10*v+b-48; return v; }
};

struct Node {
    int m[3];
    int u;
};

#define MAXN 100000
#define MAXH 18  // 1 + ceil(log2(MAXN))
struct SegTree {
    Node T[1 << MAXH];
    int n;

    void init(int N) { n = N; Zero(T); tree_init(1, 0, n-1); }
    void tree_init(int x, int a, int b) {
        if (a == b) { T[x].m[0] = 1; return; }
        int lt = 2*x, rt = lt + 1, md = (a+b)/2;
        tree_init(lt, a, md);
        tree_init(rt, md + 1, b);
        T[x].m[0] = T[lt].m[0] + T[rt].m[0];
    }

    void propagate(int x, int a, int b) {
        if (T[x].u == 0) return;

        Node aux;
        for (int i = 0; i < 3; ++i) {
            int idx = (i + T[x].u) % 3;
            aux.m[idx] = T[x].m[i];
        }
        aux.u = 0;

        if (a != b) {
            int lt = 2*x, rt = lt + 1;
            T[lt].u += T[x].u;
            T[rt].u += T[x].u;
        }
        T[x] = aux;
    }

    void update(int i, int j) { tree_update(i, j, 1, 0, n-1); }
    void tree_update(int i, int j, int x, int a, int b) {
        propagate(x, a, b);
        if (j < a || i > b) return;
        int lt = 2*x, rt = lt + 1, md = (a+b)/2;
        if (a >= i && b <= j) {
            int aux = T[x].m[0];
            T[x].m[0] = T[x].m[2];
            T[x].m[2] = T[x].m[1];
            T[x].m[1] = aux;

            if (a != b) {
                ++T[lt].u;
                ++T[rt].u;
            }
            return;
        }
        tree_update(i, j, lt, a, md);
        tree_update(i, j, rt, md + 1, b);
        for (int k = 0; k < 3; ++k)
            T[x].m[k] = T[lt].m[k] + T[rt].m[k];
    }

    int query(int i, int j) { return tree_query(i, j, 1, 0, n-1); }
    int tree_query(int i, int j, int x, int a, int b) {
        if (j < a || i > b) return 0;
        propagate(x, a, b);
        if (a >= i && b <= j) return T[x].m[0];
        int lt = 2*x, rt = lt + 1, md = (a+b)/2;
        int q1 = tree_query(i, j, lt, a, md);
        int q2 = tree_query(i, j, rt, md + 1, b);
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

        int op, i, j, ans;
        while (q--) {
            op = rr.next_u32();
            i  = rr.next_u32();
            j  = rr.next_u32();

            if (op == 0)
                tree.update(i, j);
            else {
                ans = tree.query(i, j);
                printf("%d\n", ans);
            }
        }
    }

    return 0;
}
